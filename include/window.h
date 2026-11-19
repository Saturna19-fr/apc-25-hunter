/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** window.h
*/

#ifndef WINDOW_H_
    #define WINDOW_H_
    #include <CSFML/Graphics.h>

    #define WINDOW_TITLE "MyHunter"
    #define WINDOW_WIDTH 1280
    #define WINDOW_HEIGHT 720
    #define WINDOW_MIN_WIDTH 800
    #define WINDOW_MIN_HEIGHT 600
    #define WINDOW_BPP 32
    #define WINDOW_FPS 60
    #define EXIT_ERROR 84

sfRenderWindow *create_window(void);

#endif /* !WINDOW_H_ */
