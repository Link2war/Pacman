#include <stdio.h>
#include <time.h>
#include "include/jeu.h"



int main(int argc, char **argv)
{
    initSDL();
    initTTF();

    SDL_Window* fen = createWindow("PACMAN 2025", 608, 672 + 70);
    SDL_Renderer* ren = createRenderer(fen);

    initTTF();

    jeu game = initJeu(ren);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT) {
                    game.personnage.direction = 'd';
                    if (game.start == 0) game.start = 1;
                }
                else if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_LEFT) {
                    game.personnage.direction = 'g';
                    if (game.start == 0) game.start = 1;
                }
                else if (event.key.keysym.sym == SDLK_z || event.key.keysym.sym == SDLK_UP) {
                    game.personnage.direction = 'h';
                    if (game.start == 0) game.start = 1;
                }
                else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
                    game.personnage.direction = 'b';
                    if (game.start == 0) game.start = 1;
                }
            }
        }

        game = updateJeu(game, ren);
    }

    QuitSDL(fen, ren);
    return 0;
    
}


