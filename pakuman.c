#include "pakuman.h"
#include "gestionGraphique.h"

perso initPerso (SDL_Renderer* ren){
    perso personnage;
    personnage.x = 0;
    personnage.y = 0;
    personnage.nb_deplacements = 0;
    personnage.direction = '\0';
    personnage.texture = loadTexture("ressources/pakuman_0.bmp", ren);
    return personnage;
};

perso deplacePerso (perso personage, char direction, SDL_Renderer* ren){
    if (direction == 'h'){
        personage.y = personage.y - 1;
        personage.nb_deplacements = personage.nb_deplacements + 1;
        personage.texture = loadTexture("ressources/pakuman_1.bmp", ren);
    }
    else if (direction == 'b'){
        personage.y = personage.y + 1;
        personage.nb_deplacements = personage.nb_deplacements + 1;
        personage.texture = loadTexture("ressources/pakuman_3.bmp", ren);
    }
    else if (direction == 'g'){
        personage.x = personage.x - 1;
        personage.nb_deplacements = personage.nb_deplacements + 1;
        personage.texture = loadTexture("ressources/pakuman_2.bmp", ren);
    }
    else if (direction == 'd'){
        personage.x = personage.x + 1;
        personage.nb_deplacements = personage.nb_deplacements + 1;
        personage.texture = loadTexture("ressources/pakuman_0.bmp", ren);
    }

    return personage;
};
