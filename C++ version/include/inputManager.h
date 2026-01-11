#pragma once

#include <bbop/Graphics.h>

/**
 * @class InputManager
 * @brief Gère les entrées clavier du joueur.
 * 
 * La classe InputManager est responsable de la détection des touches pressées par le joueur
 * et de la mise à jour de la direction de déplacement souhaitée (haut, bas, gauche, droite).
 * 
 * Elle ne déplace pas directement le joueur : elle se contente de stocker la **prochaine direction**
 * choisie par l’utilisateur, qui sera ensuite traitée par la classe Game.
 * 
 * Responsabilités :
 * - Lire les entrées clavier à chaque frame
 * - Mettre à jour la direction selon les touches fléchées
 * - Fournir la direction courante sous forme de `Vector2i`
 * 
 * Dépendances :
 * - GLFW : pour accéder à l’état des touches à partir de la fenêtre de jeu.
 * 
 * Exemple d’utilisation :
 * @code
 * InputManager input;
 * input.update(window);
 * Vector2i dir = input.getNextDirection();
 * @endcode
 */
class InputManager
{
private:
    Vector2i direction; ///< Direction demandée par le joueur (haut, bas, gauche, droite)

public:
    /**
     * @brief Constructeur de la classe
     * 
     * Initialise la direction à (0, 0), indiquant aucune entrée au démarrage.
     */
    InputManager();

    /**
     * @brief Met à jour la direction selon les touches pressées.
     * 
     * direction.x :
     * - prend -1 pour la gauche
     * - prend  1 pour la droite  
     * 
     * direction.y :
     * - prend -1 pour le haut
     * - prend  1 pour le bas  
     * 
     * @param window Fenêtre de jeu (GLFW), utilisée pour interroger l’état des touches.
     */
    void update(GLFWwindow* window);

    /**
     * @brief Retourne la prochaine direction saisie par le joueur.
     * 
     * @return La direction sous forme de `Vector2i`.
     */
    Vector2i getDirection() const;

    /**
     * @brief Réinitialise la direction à (0, 0)
     */
    void reset();
};
