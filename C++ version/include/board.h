#pragma once

#include <bbop/Graphics.h>

namespace BoardConstants {
    constexpr int HEIGHT = 21; ///< Nombre de cellules du plateau sur l'axe Y
    constexpr int WIDTH = 19; ///< Nombre de cellules du plateau sur l'axe X
}

/**
 * @brief Enumère toutes les tiles du plateau
 * 
 * Chaque valeur correspond à sa valeur sur le plateau et à l'indice dans textures[]
 */
enum class Tile
{
    Empty = 0,
    Wall = 1,
    Gum = 2,
    BigGum = 3,
    Pakuman = 4,
    Ghost = 5,
    Cherry = 6
};

/**
 * @class Board
 * @brief Représente le plateau de jeu de Pacman.
 * 
 * La classe Board contient la grille principale du jeu, composée de cellules (tiles)
 * représentant les murs, les gommes, le joueur, les fantômes et les bonus.
 * 
 * Ses responsabilités principales :
 * - Stocker et initialiser la disposition du niveau (table[][])
 * - Gérer les textures associées à chaque type de tile
 * - Fournir des informations sur la grille (taille, offset, contenu des cellules)
 * - Dessiner le plateau à l’écran
 * 
 * Board ne gère pas les déplacements des entités (Player, Ghosts) :
 * elle fournit seulement le contexte visuel et logique du plateau.
 */
class Board : public BbopDrawable
{
private :
    int table[BoardConstants::HEIGHT][BoardConstants::WIDTH]; ///< Grille du plateau
    Sprite* textures[7]; ///< Tableau stockant les pointeurs sur Sprites des Tiles (Wall, Gum, BigGum, etc.)
    int cellSize; ///< taille d'une cellule du plateau
    Vector2f offset; ///< offset du plateau pour centrage

    /**
     * @brief Initialise la grille du plateau avec les tiles de départ
     */
    void initLayout();

    /**
     * @brief Initialise l'offset du plateau
     * 
     * Calcule la taille des cellules et l'offset
     */
    void initOffset();

    /**
     * @brief Initialise les textures du plateau
     * 
     * Charge et configure les textures dans le tableau textures[]
     */
    void initTextures();

public :
    /**
     * @brief Constructeur de la classe
     * 
     * Initialise la grille, l'offset, la taille des cellules et les textures
     */
    Board();

    /**
     * @brief Destructeur de la classe
     * 
     * Est un destructeur virtual parce que la classe hérite de BbopDrawable et possède une méthode override
     * Détruit les pointeurs de Sprite stockées dans le tableau de textures
     */
    virtual ~Board();

    /**
     * @brief Dessine chaque cellule du plateau.
     *
     * Parcourt la grille et affiche la texture correspondante
     * (mur, gomme, fantôme, etc.) sauf les cases vides.
     */
    void Draw(GLint* renderUniform) const override;

    /**
     * @brief Met à jour la position à l'écran de tous les Sprites du plateau
     * 
     * Parcourt la grille du plateau et repositionne chaque Sprite non vide
     * (mur, gomme, fantôme, pakuman, cerise, etc.) en fonction de sa position
     * logique dans le tableau `table`, de la taille des cellules (`cellSize`)
     * et de l'offset du plateau (`offset`).  
     * Cette méthode permet de séparer la logique de la grille et l'affichage,
     * et doit être appelée chaque fois que `offset` ou `cellSize` change, 
     * ou après modification des tiles.
     */
    void updateScreenPosition();

    /**
     * @brief Modifie la tile de la cellule posX, posY par une autre tile
     * 
     * @param posX Position X de la tile
     * @param posY Position Y de la tile
     * @param tile Nouvelle Tile de la cellule
     */
    void setTile(int posX, int posY, Tile tile); 

    /**
     * @brief Retourne la tile de la cellule posX, posY
     * 
     * @param posX Position X de la tile
     * @param posY Position Y de la tile
     * @return Tile la tile de la cellule
     */
    Tile getTile(int posX, int posY) const;

    /**
     * @brief Retourne la position du tile du Player(Pakuman) sur le plateau
     * 
     * @return Vector2i Position du tile dans le tableau (indices entiers), retourne Vector2f(-1, -1) si la tile n'est pas trouvée
     */
    Vector2i getPlayerPosition() const;

    int getGhostsNumber() const;

    /**
     * @brief Retourne la position des tiles de chaque Ghost sur le plateau
     */
    void getGhostsPosition(std::vector<Vector2i> &ghostsPosition) const;

    /**
     * @brief Retourne l'offset du plateau
     * 
     * A fournir aux objets indépendants de Board (Player, Ghost, etc.)
     * Permet de mettre à jour la position des Sprites sur l'écran
     */
    Vector2f getOffset() const;

    /**
     * @brief Retourne la taille des cellules (cellSize)
     * 
     * A fournir aux objets indépendants de Board (Player, Ghost, etc.)
     * Permet de redimensionner proportionnellement les Sprites aux cellules du plateau
     */
    int getCellSize() const;

    /**
     * @brief Réinitialise le plateau
     * 
     * génère de nouveau le plateau
     */
    void reset();
};