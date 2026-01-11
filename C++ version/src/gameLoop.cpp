#include "../include/gameLoop.h"


GameLoop::GameLoop(GLFWwindow* _window) :
    window(_window),
    gameplay()
{
    
}

GameLoop::~GameLoop()
{
    // destruction de la fenêtre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();
}

void GameLoop::run()
{
    while (!glfwWindowShouldClose(window))
    {
        bbopCleanWindow(window,Vector3i(0,0,0),1.0f);

        updateGameplay();
        drawGameplay();
        
        bbopErrorCheck();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameLoop::updateGameplay()
{
    gameplay.update(window);
}

void GameLoop::drawGameplay()
{
    gameplay.Draw();
}