#pragma once

#include <bbop/Graphics.h>


/**
 * @class GameCharacter
 * @brief Représente un personnage dans le jeu.
 * 
 * La classe GameCharacter gère l'état du personnage :
 * - sa position sur le plateau (en coordonnées de tiles)
 * - sa position sur l'écran
 * - sa direction de déplacement
 * - son sprite affiché à l'écran
 * 
 * Elle gère l'affichage du sprite mais pas son changement de texture.
 * Le changement de texture se fait dans une classe fille
 * 
 * GameCharacter hérite de BbopDrawable afin de pouvoir être dessiné par le moteur graphique.
 */
class GameCharacter : public BbopDrawable
{
protected :
    Sprite sprite; ///< Sprite du personnage (stocke la position du personnage sur l'écran)
    Vector2i startTilePosition; ///< Position de départ sur le plateau
    Vector2i tilePosition; ///< Position sur le plateau (index)
    Vector2i direction; ///< Direction actuelle

    /**
     * @brief Initialise le Sprite du personnage
     * 
     * Initialise : la texture, la taille, l'origine et la position sur l'écran
     * @param boardOffset Offset du plateau pour la position du Sprite
     * @param cellSize Taille des cellules du plateau pour la position du Sprite
     */
    virtual void initSprite(Vector2f boardOffset, int cellSize) = 0;

public :
    /**
     * @brief Constructeur de la classe
     * 
     * Initialise la position du plateau et la direction du personnage
     * @param _startTilePosition Position de départ du personnage sur le plateau
     */
    GameCharacter(Vector2i _startTilePosition);

    /**
     * @brief Destructeur de la classe
     */
    virtual ~GameCharacter() = default;

    /**
     * @brief Dessine le personnage sur l'écran
     * 
     * Dessine le Sprite du personnage
     */
    virtual void Draw(GLint* renderUniform) const override;

    /**
     * @brief Met à jour la position du personnage sur le plateau
     * 
     * @param newTilePosition Position de la nouvelle tile
     */
    void setTilePosition(Vector2i newTilePosition);

    /**
     * @brief Retourne la position de la tile sur le plateau
     * 
     * Permet de vérifier les collisions et mettre à jour la position du personnage dans la classe Game
     */
    Vector2i getTilePosition() const;

    /**
     * @brief Modifie la direction
     * 
     * @param newDirection Nouvelle direction du personnage
     */
    void setDirection(Vector2i newDirection);

    /**
     * @brief Retourne la direction du personnage
     * 
     * Permet de mettre à jour la position du personnage dans la classe Game
     */
    Vector2i getDirection() const;

    /**
     * @brief Met à jour la position du personnage sur l'écran
     * 
     * @param boardOffset Offset du plateau
     * @param cellSize Taille des cellules du plateau
     */
    void updateScreenPosition(Vector2f boardOffset, int cellSize);

    /**
     * @brief Met à jour la texture du Sprite
     */
    virtual void updateTexture() = 0; ///< Spécifique à chaque personnage

    /**
     * @brief Réinitialise le personnage
     * 
     * Réinitialise la position et la direction
     */
    virtual void reset();
};
