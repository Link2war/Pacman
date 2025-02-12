#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <time.h>
#include "gestionGraphique.h"
#include "plateau.h"
#include "pakuman.h"
#include "fantome.h"

#define MOVE_DELAY 200 // Temps en ms entre chaque déplacement (200ms = 5 cases/seconde)

struct jeu
{
    plateau plat;
    perso personnage;
    fantome ghost;
    SDL_Texture* textures[7];

    Uint32 lastMoveTime; // Temps du dernier mouvement
    int play;
    int start;
    int end;

    int score;
    int cerise;

    TTF_Font* font;
    char * text;
    SDL_Color color;
};
typedef struct jeu jeu;

jeu initJeu(SDL_Renderer* ren);
jeu updateJeu(jeu j, SDL_Renderer* ren);

int gagner(plateau plat);
int perdue(plateau plat);

#endif