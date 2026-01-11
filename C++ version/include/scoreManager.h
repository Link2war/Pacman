#pragma once

/**
 * @brief Classe pour gérer le score du joueur.
 * 
 * Permet d'ajouter des points pour différents types d'objets collectés
 * (gum, big gum, cherry) et de récupérer le score actuel.
 */
class ScoreManager
{
private:
    int score; ///< score total du joueur

public:
    /**
     * @brief Constructeur
     * 
     * Initialise le score à 0.
     */
    ScoreManager();

    /**
     * @brief Réinitialise le score à zéro
     */
    void reset();

    /**
     * @brief Ajoute des points pour une gum normale
     */
    void addGum();

    /**
     * @brief Ajoute des points pour une big gum
     */
    void addBigGum();

    /**
     * @brief Ajoute des points pour une cherry
     */
    void addCherry();

    /**
     * @brief Retourne le score actuel
     * @return int score total
     */
    int getScore() const;
};
