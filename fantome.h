#ifndef FANTOME_H
#define FANTOME_H

#include "gestionGraphique.h"
#include <string.h>
#include <stdlib.h>

struct fantome
{
    char direction;
    SDL_Texture* texture;
    char deplacement;
    int valeur;
};
typedef struct fantome fantome;

fantome initFantome(SDL_Renderer* ren);
fantome deplaceGhost(fantome ghost, char direction, SDL_Renderer* ren);

#endif