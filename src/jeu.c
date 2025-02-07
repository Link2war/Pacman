#include "jeu.h"

jeu initJeu(SDL_Renderer* ren)
{
    jeu game;
    game.plat = initPlateau();

    game.personnage = initPerso(ren);
    game.ghost = initFantome(ren);

    game.textures[1] = loadTexture("../ressources/wall.bmp", ren);
    game.textures[2] = loadTexture("../ressources/gum.bmp", ren);
    game.textures[3] = loadTexture("../ressources/bigGum.bmp", ren);
    game.textures[4] = game.ghost.texture;
    game.textures[5] = loadTexture("../ressources/cherry.bmp", ren);
    game.textures[6] = game.personnage.texture;

    game.lastMoveTime = SDL_GetTicks();
    game.play = 0;

    return game;

}

jeu updateJeu(jeu game, SDL_Renderer* ren)
{
    if (game.play == 1)
    {
        game.ghost.direction = 'h';
        
        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - game.lastMoveTime >= MOVE_DELAY) {
            
            game.personnage = deplacePerso(game.personnage, game.direction, ren);
            game.ghost = deplaceGhost(game.ghost, game.direction, ren);

            game.textures[4] = game.ghost.texture;
            game.textures[6] = game.personnage.texture;

            game.plat = moveFantome(game.plat, &game.ghost.direction);
            game.plat = movePlayer(game.plat, game.personnage.x, game.personnage.y);
            game.personnage.x = 0;
            game.personnage.y = 0;

            game.lastMoveTime = currentTime;
        }
        
    }
    
    clearRenderer(ren);
    affichePlateau(game.plat, game.textures, ren);
    updateDisplay(ren);

    return game;
}