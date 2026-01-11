#pragma once

#include <bbop/Graphics.h>

#include "board.h"
#include "inputManager.h"
#include "scoreManager.h"
#include "player.h"
#include "ghost.h"

constexpr float FRAME_DELAY = 0.25f;

/**
 * @brief Enumère les différents états du jeu
 * 
 * Playing correspond à la mise à jour de la partie (update)
 * GameOver et Victory correspondent à la fin de la partie (reset)
 */
enum class GameState
{
    Playing,
    GameOver,
    Victory
};

/**
 * @class Game
 * @brief Classe principale gérant la boucle de jeu.
 * 
 * La classe Game orchestre l’ensemble du fonctionnement du jeu :
 * - initialisation des ressources et des objets (plateau, joueur, entrées, interface)
 * - exécution de la boucle principale (`run()`)
 * - mise à jour de la logique du jeu (`update()`)
 * - affichage de la scène (`Draw()`)
 * - réinitialisation de la partie (`reset`)
 * 
 * Elle relie les composants principaux :
 * - `Board` : plateau du jeu contenant les murs, gommes et bonus.
 * - `Player` : personnage contrôlé par le joueur (Pakuman).
 * - `InputManager` : gestion des entrées clavier.
 * - `ScoreManager` : gestion du score
 * - `TextBox` : affichage du score à l’écran.
 * 
 * Le système de temps (`deltaTime`, `timer`, `delay`) permet de réguler la fréquence d’exécution
 * et d’assurer une vitesse de jeu constante.
 */
class Gameplay
{
private:
    Scene scene; ///< Scène de rendu BBOP.
    GameState state;  ///< état actuel du jeu
    Board board; ///< Plateau de jeu (murs, gommes, bonus).
    InputManager inputManager; ///< Gestionnaire des entrées clavier.
    ScoreManager scoreManager;
    Player player; ///< Joueur contrôlé (Pakuman).
    std::vector<Ghost> ghosts;
    Font font; ///< Police utilisée pour le texte.
    TexteBox textScore; ///< Zone d’affichage du score.

    float deltaTime; ///< Temps écoulé entre deux frames (en secondes).
    float delay; ///< Délai minimal entre deux mises à jour pour limiter la vitesse du jeu.
    float timer; ///< Chronomètre interne pour la régulation de la boucle de jeu.
    double lastFrame; ///< Temps de la dernière frame, pour calcul du deltaTime.

    /**
     * @brief Initialise la boîte de text pour le score
     */
    void initTextScore();

    /**
     * @brief Initialise le personnage du joueur
     */
    void initPlayer();

    /**
     * @brief Initialise les fantômes
     */
    void initGhosts();

public:
    Gameplay();

    /**
     * @brief Destructeur de la classe Game.
     * 
     * Libère les ressources associées à la scène et détruit les objets internes.
     */
    ~Gameplay();

    /**
     * @brief Met à jour la logique du jeu.
     * 
     * Appelle les fonctions de mise à jour des entités du jeu
     * (joueur, score, plateau, etc.).
     */
    void update(GLFWwindow* _window);

    /**
     * @brief Dessine tous les éléments du jeu à l’écran.
     * 
     * Affiche le plateau, le joueur et l’interface utilisateur.
     */
    void Draw();

    /**
     * @brief Met à jour le deltaTime.
     * 
     * Calcule le temps écoulé entre la frame actuelle et la précédente.
     */
    void updateDeltaTime();

    /**
     * @brief Met à jour le timer interne.
     * 
     * Sert à gérer le délai (`delay`) pour limiter le nombre de frames par seconde.
     */
    void updateTimer();

    /**
     * @brief Met à jour la zone de texte affichant le score.
     */
    void updateTextBox();

    /**
     * @brief Met à jour l’état du joueur.
     * 
     * Cette méthode regroupe :
     * - la gestion de la direction (via `updatePlayerDirection()`)
     * - le déplacement du joueur (via `updatePlayerPosition()`)
     * - la mise à jour du score selon les éléments collectés.
     */
    void updatePlayer();

    /**
     * @brief Met à jour la direction du joueur.
     * 
     * Change la direction du joueur uniquement si la direction choisie
     * n’est pas bloquée par un mur.
     */
    void updatePlayerDirection();

    /**
     * @brief Met à jour la position du joueur.
     * 
     * Déplace le joueur sur la grille si la prochaine case n’est pas un mur.
     */
    void updatePlayerPosition();

    /**
     * @brief Met à jour l’état des Ghosts.
     * 
     * Cette méthode regroupe :
     * - la gestion de la direction (via `updateGhostDirection()`)
     * - le déplacement du Ghost (via `updateGhostPosition()`)
     * - la mise à jour de la texture.
     */
    void updateGhosts();

    /**
     * @brief Met à jour la direction du Ghost.
     * 
     * Génère une direction aléatoire (ne pouvant être la direction opposée).
     * Change la direction du Ghost uniquement si la direction choisie
     * n’est pas bloquée par un mur.
     * @param ghost Fantome à modifier
     */
    void updateGhostDirection(Ghost& ghost);

    /**
     * @brief Met à jour la position du Ghost
     * @note Déplace le Ghost sur la grille si la prochaine case n’est pas un mur.
     * @param ghost Fantome à modifier
     */
    void updateGhostPosition(Ghost& ghost);

    /**
     * @brief Change l'état du jeu en GameOver
     */
    void handleGameOver();

    /**
     * @brief Change l'état du jeu en Victory
     */
    void handleVictory();

    /**
     * @brief Vérifie si le joueur est attrapé par un fantôme
     * @return True si le joueur est sur la même cellule qu'un fantôme, False sinon
     */
    bool ghostCaughtPlayer();

    /**
     * @brief Réinitialise la partie de jeu sauf le score total
     */
    void restart();
};