#include "fantome.h"

fantome initFantome(SDL_Renderer* ren)
{
    fantome ghost;
    ghost.texture = loadTexture("../ressources/ghost1_0.bmp", ren);

    return ghost;
}

fantome deplaceGhost(fantome ghost, char direction, SDL_Renderer* ren)
{
    if (direction == 'h')
    {
        ghost.texture = loadTexture("../ressources/ghost1_1.bmp", ren);
    }
    else if (direction == 'b')
    {
        ghost.texture = loadTexture("../ressources/ghost1_3.bmp", ren);
    }
    else if (direction == 'g')
    {
        ghost.texture = loadTexture("../ressources/ghost1_2.bmp", ren);
    }
    else if (direction == 'd')
    {
        ghost.texture = loadTexture("../ressources/ghost1_0.bmp", ren);
    }

    return ghost;
}