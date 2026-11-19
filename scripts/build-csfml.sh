#!/bin/sh
# Compile SFML 3 et CSFML 3 (sans le module audio) dans un préfixe local.
# Ubuntu ne fournit que la CSFML 2 : la release Linux a besoin de ce build.
# Usage : scripts/build-csfml.sh <préfixe>
set -eu

prefix="${1:?usage: build-csfml.sh <prefixe>}"
sfml_version="${SFML_VERSION:-3.0.2}"
csfml_version="${CSFML_VERSION:-3.0.0}"
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT

mkdir -p "$prefix"
prefix="$(cd "$prefix" && pwd)"

build() {
    name="$1"
    shift
    cmake -S "$work/$name" -B "$work/$name/build" \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        -DCMAKE_INSTALL_PREFIX="$prefix" \
        -DCMAKE_INSTALL_LIBDIR=lib \
        -DCMAKE_PREFIX_PATH="$prefix" \
        "$@"
    cmake --build "$work/$name/build" --parallel
    cmake --install "$work/$name/build"
}

git clone --depth 1 --branch "$sfml_version" \
    https://github.com/SFML/SFML.git "$work/SFML"
build SFML -DSFML_BUILD_AUDIO=OFF

git clone --depth 1 --branch "$csfml_version" \
    https://github.com/SFML/CSFML.git "$work/CSFML"
build CSFML -DCSFML_BUILD_AUDIO=OFF
