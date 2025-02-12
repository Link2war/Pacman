#include "jeu.h"

jeu initJeu(SDL_Renderer* ren)
{
    jeu game;

    game.plat = initPlateau();
    game.personnage = initPerso(ren);
    game.ghost = initFantome(ren);

    game.textures[1] = loadTexture("ressources/wall.bmp", ren);
    game.textures[2] = loadTexture("ressources/gum.bmp", ren);
    game.textures[3] = loadTexture("ressources/bigGum.bmp", ren);
    game.textures[4] = game.ghost.texture;
    game.textures[5] = loadTexture("ressources/cherry.bmp", ren);
    game.textures[6] = game.personnage.texture;

    game.lastMoveTime = SDL_GetTicks();
    game.play = 0;
    game.start = 0;
    game.end = 0;

    game.score = 0;
    game.font = createFont("ressources/DejaVuSans-Bold.ttf", 50);
    game.text = malloc(12 * sizeof(char)); 
    game.color = (SDL_Color){255, 255, 255, 255};

    return game;

}

jeu updateJeu(jeu game, SDL_Renderer* ren)
{
    if (game.start == 1)
    {
        game.play = 1;
    }
    if (game.play == 1)
    {
        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - game.lastMoveTime >= MOVE_DELAY)
        {
            game.personnage = deplacePerso(game.personnage, game.personnage.direction, ren);
            game.ghost = deplaceGhost(game.ghost, game.ghost.direction, ren);
            game.textures[4] = game.ghost.texture;
            game.textures[6] = game.personnage.texture;

            game.plat = movePlayer(game.plat, game.personnage.x, game.personnage.y, &game.score);

            if (gagner(game.plat) == 1)
            {
                game.play = 0;
                game.end = 1;
                game.text = "Bravo, vous avez gagné";
            }
            if (perdue(game.plat) == 1)
            {
                game.play = 0;
                game.end = 1;
                game.text = "Dommage, vous avez perdue";
            }
            else 
            {
                game.plat = moveFantome(game.plat, &game.ghost.direction, game.start);
                game.personnage.x = 0;
                game.personnage.y = 0;
            }

            if (perdue(game.plat) == 1)
            {
                game.play = 0;
                game.end = 1;
                game.text = "Dommage, vous avez perdue";
                return game;
            }

            if (game.start == 1)
            {
                game.start = 2;
            }
            
            game.lastMoveTime = currentTime;
        }
    }

    // conversion du int en char *
    if (game.end != 1) 
    {
        sprintf(game.text, "%d", game.score);
    }
    
    // affichage
    clearRenderer(ren);
    affichePlateau(game.plat, game.textures, ren);

    if (game.end == 0) 
    {
        printText(10, 10, game.text, 50, 50, game.font, game.color, ren);
    }
    else 
    {
        printText(5, 300, game.text, 600, 100, game.font, game.color, ren);
    }
    updateDisplay(ren);


    return game;
}

int gagner(plateau plat)
{
    for (int i=0; i<MAP_HEIGHT_MAX; i++)
    {
        for (int j=0; j<MAP_WIDHT_MAX; j++)
        {
            if (plat.map[i][j] == 2 || plat.map[i][j] == 3 || plat.map[i][j] == 5) 
            {
                return 0;
            }
        }
    }
    return 1;
}

int perdue(plateau plat)
{
    
    struct position posPlayer = trouvePlayer(plat);
    struct position posGhost = trouveFantome(plat);

    if (posGhost.x == posPlayer.x && posPlayer.y == posGhost.y)
    {
        return 1;
    }

    return 0;
}