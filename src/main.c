#include <stdio.h>
#include <time.h>
#include "jeu.h"



int main(int argc, char **argv)
{
    initSDL();
    initTTF();

    SDL_Window* fen = createWindow("PACMAN 2025", 608, 672);
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
                    game.direction = 'd';
                    game.play = 1;
                }
                else if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_LEFT) {
                    game.direction = 'g';
                    game.play = 1;
                }
                else if (event.key.keysym.sym == SDLK_z || event.key.keysym.sym == SDLK_UP) {
                    game.direction = 'h';
                    game.play = 1;
                }
                else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
                    game.direction = 'b';
                    game.play = 1;
                }
            }
        }

        game = updateJeu(game, ren);
    }

    QuitSDL(fen, ren);
    return 0;
    
}


