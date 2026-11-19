/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** main.c
*/

#include "game.h"
#include "my.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static const char HELP[] =
    "MY HUNTER - Duck Hunt en réseau (2 à 4 joueurs)\n\n"
    "USAGE\n"
    "    ./my_hunter                      ouvre le menu\n"
    "    ./my_hunter --host [pseudo [ip]] héberge directement une partie\n"
    "                                     (ip : adresse de l'interface "
    "d'écoute)\n"
    "    ./my_hunter --join ip [pseudo]   rejoint la partie hébergée sur ip\n"
    "    ./my_hunter -h                   affiche cette aide\n\n"
    "COMMENT JOUER\n"
    "    Un joueur héberge, les autres tapent son adresse puis Rejoindre.\n"
    "    Tout le monde voit les mêmes canards : le premier qui clique\n"
    "    dessus marque le point. La manche dure 60 secondes.\n\n"
    "TOUCHES\n"
    "    Clic gauche   tirer / cliquer sur un bouton\n"
    "    Tab           changer de champ dans le menu\n"
    "    Echap         quitter la partie en cours\n";

static int print_help(void)
{
    my_putstr(HELP);
    return 0;
}

static int fail(app_t *app, const char *message)
{
    write(STDERR_FILENO, message, my_strlen(message));
    app_destroy(app);
    return EXIT_ERROR;
}

static void apply_args(app_t *app, int argc, const char *argv[])
{
    bool host = argc > 1 && my_strcmp(argv[1], "--host") == 0;
    bool join = argc > 2 && my_strcmp(argv[1], "--join") == 0;
    int name_arg = join ? 3 : 2;
    bool bound = !host || argc <= 3 || session_bind(app, argv[3]);

    if ((host || join) && argc > name_arg)
        str_copy(app->name, argv[name_arg], NAME_LEN);
    if (join)
        str_copy(app->host, argv[2], HOST_LEN);
    if (host && bound)
        session_host(app);
    if (join)
        session_join(app);
}

int main(int argc, const char *argv[])
{
    app_t app;

    if (argc > 1 && my_strcmp(argv[1], "-h") == 0)
        return print_help();
    srand((unsigned int)time(NULL));
    if (!app_create(&app))
        return fail(&app,
            "my_hunter: assets introuvables, lance le jeu "
            "depuis la racine du projet\n");
    apply_args(&app, argc, argv);
    while (sfRenderWindow_isOpen(app.window)) {
        handle_events(&app);
        app_update(&app, sfTime_asSeconds(sfClock_restart(app.clock)));
        app_draw(&app);
    }
    app_destroy(&app);
    return 0;
}
