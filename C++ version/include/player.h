#pragma once

#include <bbop/Graphics.h>
#include "gameCharacter.h"

/**
 * @class Player
 * @brief Représente le joueur (Pakuman) dans le jeu.
 * 
 * Player hérite de GameCharacter afin de pouvoir contrôlé par le joueur :
 * - sa position de départ sur le plateau (en coordonnées de tiles)
 * - sa position sur le plateau (en coordonnées de tiles)
 * - sa position sur l'écran
 * - sa direction de déplacement
 * - son sprite affiché à l'écran
 * 
 * La classe ne gère pas la logique du plateau (collisions, murs, etc.)
 */
class Player : public GameCharacter
{
private :
    /**
     * @brief Initialise le Sprite du Joueur
     * 
     * Initialise : la texture, la taille, l'origine et la position sur l'écran
     * @param boardOffset Offset du plateau pour la position du Sprite
     * @param cellSize Taille des cellules du plateau pour la position du Sprite
     */
    void initSprite(Vector2f boardOffset, int cellSize) override;

public :
    /**
     * @brief Constructeur de la classe
     * 
     * Initialise le Sprite, la position du Sprite sur l'écran et la position du tile sur le plateau
     * @param tilePosition Position de la tile sur le plateau
     * @param boardOffset Offset du plateau pour initialiser la position du sprite sur l'écran
     * @param cellSize Taille d'une cellule pour initialiser la position du sprite sur l'écran et rendre le Sprite proportionnelle aux cellules du plateau
     */
    Player(Vector2i _tilePosition, Vector2f boardOffset, int cellSize);

    /**
     * @brief Destructeur de la classe
     * 
     * Est virtual parce que la classe hérite de BbopDrawable et possède une méthode override.
     */
    virtual ~Player() = default;

    /**
     * @brief Met à jour la texture du Sprite
     * 
     * Change la texture du Sprite selon la direction du Player (up, down, left, right)
     */
    void updateTexture() override;

    /**
     * @brief reset du joueur
     * 
     * Réinitialise la position, direction et la texture du sprite
     */
    void reset() override;
};