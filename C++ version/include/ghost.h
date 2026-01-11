#pragma once

#include <bbop/Graphics.h>
#include "gameCharacter.h"

/**
 * @brief Couleur du fantôme
 * 
 * Sert d'index pour le changement de texture
 */
enum GhostColor
{
    Red = 0,
    Pink = 1,
    Cyan = 2,
    Orange = 3
};

/**
 * @class Ghost
 * @brief Représente l'ennemi' (Ghost) dans le jeu.
 * 
 * Ghost hérite de GameCharacter afin de pouvoir contrôlé par lui-même :
 * - sa position de départ sur le plateau (en coordonnées de tiles)
 * - sa position sur le plateau (en coordonnées de tiles)
 * - sa position sur l'écran
 * - sa direction de déplacement
 * - son sprite affiché à l'écran
 * 
 * La classe ne gère pas la logique du plateau (collisions, murs, etc.)
 */
class Ghost : public GameCharacter
{
private :
    GhostColor color; ///< Couleur du Ghost, sert comme index pour le changement de texture

    /**
     * @brief Initialise le Sprite du Fantome
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
    Ghost(Vector2i _tilePosition, Vector2f boardOffset, int cellSize, GhostColor _color);

        /**
     * @brief Destructeur de la classe
     * 
     * Est virtual parce que la classe hérite de BbopDrawable et possède une méthode override.
     */
    virtual ~Ghost() = default;

    /**
     * @brief Met à jour la texture du Sprite
     * 
     * Change la texture du Sprite selon la direction du Ghost (up, down, left, right)
     * et selon la couleur du fantome
     */
    void updateTexture() override;

    /**
     * @brief reset du fantome
     * 
     * Réinitialise la position, direction et la texture du sprite
     */
    void reset() override;
};