#pragma once

#include <bbop/Graphics.h>
#include "gameplay.h"


class GameLoop
{
private:
    GLFWwindow* window; ///< Fenêtre de jeu.
    Gameplay gameplay;

public:
    
    GameLoop(GLFWwindow* _window);

    
    ~GameLoop();

    
    void run();

    
    void updateGameplay();

    
    void drawGameplay();
};