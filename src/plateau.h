#ifndef PLATEAU_H
#define PLATEAU_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gestionGraphique.h"
#define SIZE 32
#define MAP_HEIGHT_MAX 21
#define MAP_WIDHT_MAX 19


struct plateau
{
    int map[MAP_HEIGHT_MAX][MAP_HEIGHT_MAX];
};
typedef struct plateau plateau;

plateau initPlateau();
void affichePlateau(plateau plat, SDL_Texture* textures[], SDL_Renderer *ren);

struct position
{
    int x;
    int y;
};

/* @brief retourne la case du joueur dans la plat.map sous forme de vecteur x,y
@note sous entend qu'il n'y a qu'un joueur dans le plateau */
struct position trouvePlayer(plateau plat);

/* @brief retourne la case du fantome dans la plat.map sous forme de vecteur x,y
@note sous entend qu'il n'y a qu'un fantome dans le plateau */
struct position trouveFantome(plateau plat);

plateau moveFantome(plateau plat, char * direction);

/* @brief Modifie la valeur du pakman dans la plat.map
@note si x = 1, le joueur se déplace à droite
@note si x = -1, le joueur se déplace à gauche
@note si y = 1, le joueur se déplace en bas
@note si y = -1, le joueur se déplace en haut
@note réinitialise les positions x et y du pac pour les cases suivantes
*/
plateau movePlayer(plateau plat, int x, int y);

#endif
