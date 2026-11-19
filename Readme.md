# My Hunter — Duck Hunt en réseau

Démo en C avec la CSFML 3 : de 2 à 4 joueurs chassent les mêmes canards, chacun
sur sa machine. Le premier qui clique sur un canard marque le point ; la manche
dure 60 secondes.

## Télécharger le jeu

Chaque push sur `event/apc-25-nov` publie une archive prête à jouer, avec les
bibliothèques incluses, dans la
[release `latest`](../../releases/tag/latest) : Linux x86_64 et macOS Apple
Silicon. Décompresse l'archive et lis `LISEZMOI.txt`.

Pour fabriquer l'archive à la main : `make && scripts/package.sh macos`
(nécessite `brew install dylibbundler`).

## Lancer une partie

```sh
make
./my_hunter          # à lancer depuis la racine du projet (dossier assets/)
```

1. Un joueur clique sur **Héberger** : son adresse IP s'affiche dans le salon.
2. Les autres tapent cette adresse dans le menu puis cliquent sur **Rejoindre**.
3. L'hôte clique sur **Lancer la partie**.

Raccourcis en ligne de commande :

```sh
./my_hunter --host Alice                # héberge directement
./my_hunter --host Alice 100.101.102.103  # héberge sur une interface précise
./my_hunter --join 192.168.1.42 Bob     # rejoint directement
./my_hunter -h                          # aide
```

Le sélecteur « Interface d'écoute » du menu choisit sur quelle adresse l'hôte
attend les joueurs : toutes, ou une seule (Wi-Fi, Tailscale...). Clic à droite
du champ pour la suivante, à gauche pour la précédente. Les joueurs doivent
pouvoir joindre cette adresse (même réseau local, ou même tailnet). Le jeu écoute sur le port TCP
4242 ; s'il est occupé, il prend le suivant et le salon affiche `ip:port`, à
taper tel quel pour rejoindre.

## Comment ça marche

L'hôte fait autorité : lui seul simule le jeu.

| Sens | Message | Contenu |
|---|---|---|
| client → hôte | `MSG_HELLO` | pseudo |
| client → hôte | `MSG_CURSOR` | position du viseur, 30 fois par seconde |
| client → hôte | `MSG_SHOOT` | position du tir |
| hôte → client | `MSG_STATE` | phase, temps restant, joueurs, canards, 30 fois par seconde |

Les clients affichent l'état reçu et prolongent le mouvement des canards entre
deux messages. Tout passe par le module Network de la CSFML (`sfTcpListener`,
`sfTcpSocket`, `sfPacket`), en sockets non bloquants.

## Organisation du code

| Fichiers | Rôle |
|---|---|
| `src/world.c`, `src/ducks.c` | règles du jeu et canards, sans aucun affichage |
| `src/net_host.c`, `src/net_client.c` | côté hôte et côté client |
| `src/net_packet.c`, `src/net_common.c` | format des messages, envoi, fermeture |
| `src/ifaces.c` | liste des interfaces réseau de la machine |
| `src/scene_*.c` | menu, salon / fin de manche, partie |
| `src/draw.c`, `src/ui_widgets.c` | texte, boîtes, viseur, boutons, champs |
| `src/app.c`, `src/loop.c`, `src/window.c`, `src/session.c` | cycle de vie, boucle, événements |

La simulation et le réseau ne dépendent pas de la fenêtre : on pourra en tirer
un serveur dédié ou un relais sans réécrire le jeu.
