#ifndef PERSO_H
#define PERSO_H

#include "gestionGraphique.h"
#include <string.h>
#include <stdlib.h>
/*#include "plateau.h"*/

#define HAUT 10
#define LARG 10
#define NBDEPMAX 40

struct persoST
{
    SDL_Texture* texture;
    int x;
    int y;
    int nb_deplacements;
};
typedef struct persoST perso;


perso initPerso (SDL_Renderer* ren);
perso deplacePerso (perso personage, char direction, SDL_Renderer* ren);

#endif