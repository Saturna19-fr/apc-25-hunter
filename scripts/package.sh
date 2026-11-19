#!/bin/sh
# Fabrique une archive autonome du jeu : binaire, bibliothèques externes,
# assets et lanceur. Le jeu doit déjà être compilé (make).
# Usage : scripts/package.sh linux|macos
#   Linux : CSFML_DIR doit pointer sur le préfixe de scripts/build-csfml.sh.
set -eu

os="${1:?usage: package.sh linux|macos}"
root="$(cd "$(dirname "$0")/.." && pwd)"
name="my_hunter-$os-$(uname -m)"
dist="$root/dist"
out="$dist/$name"

fail() {
    echo "package.sh: $1" >&2
    exit 1
}

bundle_linux() {
    csfml="$(cd "${CSFML_DIR:?CSFML_DIR manquant}" && pwd)"
    LD_LIBRARY_PATH="$csfml/lib" ldd "$root/my_hunter" | awk '$2 == "=>" && $3 ~ /^\// {print $3}' |
        grep "^$csfml/" | while read -r lib; do
        cp -L "$lib" "$out/libs/"
    done
    patchelf --set-rpath '$ORIGIN/libs' "$out/my_hunter"
    for lib in "$out"/libs/*; do
        patchelf --set-rpath '$ORIGIN' "$lib"
    done
    if ldd "$out/my_hunter" | grep -E "not found|$csfml/"; then
        fail "des bibliothèques ne sont pas embarquées"
    fi
    launcher="jouer.sh"
}

bundle_macos() {
    brew_prefix="$(brew --prefix)"
    dylibbundler -od -b -x "$out/my_hunter" -d "$out/libs/" \
        -p @executable_path/libs/ -s "$(brew --prefix sfml)/lib" < /dev/null
    install_name_tool -delete_rpath "$(brew --prefix csfml)/lib" \
        "$out/my_hunter" 2> /dev/null || true
    codesign --force -s - "$out"/libs/*.dylib "$out/my_hunter"
    if otool -L "$out/my_hunter" "$out"/libs/*.dylib |
        grep -E "^[[:space:]]+($brew_prefix|/usr/local)/"; then
        fail "des bibliothèques ne sont pas embarquées"
    fi
    launcher="Jouer.command"
}

write_launcher() {
    cat > "$out/$launcher" << 'LAUNCHER'
#!/bin/sh
# Le jeu charge ses images depuis le dossier courant.
cd "$(dirname "$0")" || exit 1
exec ./my_hunter "$@"
LAUNCHER
    chmod +x "$out/$launcher"
}

write_readme() {
    cat > "$out/LISEZMOI.txt" << README
MY HUNTER - Duck Hunt en réseau (2 à 4 joueurs)

LANCER
    Linux : ./jouer.sh
    macOS : double-clic sur Jouer.command

    macOS bloque les programmes téléchargés non signés. Avant le premier
    lancement, ouvre un Terminal dans ce dossier et tape :
        xattr -dr com.apple.quarantine .

JOUER
    Un joueur clique sur Héberger et donne l'adresse affichée aux autres.
    Les autres tapent cette adresse puis cliquent sur Rejoindre.
    L'hôte lance la partie : le premier qui clique sur un canard marque.

    Aide complète : ./jouer.sh -h (ou ./Jouer.command -h)

PRÉREQUIS
    Linux : un bureau avec X11 (ou XWayland) et OpenGL.
    macOS : Mac Apple Silicon, macOS 15 ou plus récent.
README
}

[ -x "$root/my_hunter" ] || fail "my_hunter introuvable, lance make d'abord"
rm -rf "$out"
mkdir -p "$out/libs"
cp "$root/my_hunter" "$out/"
cp -R "$root/assets" "$out/"
case "$os" in
    linux) bundle_linux ;;
    macos) bundle_macos ;;
    *) fail "système inconnu : $os" ;;
esac
write_launcher
write_readme
tar -C "$dist" -czf "$dist/$name.tar.gz" "$name"
echo "$dist/$name.tar.gz"
