#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <bbop/Graphics.h>

#include "include/gameLoop.h"


int main()
{
    //creation de la fenêtre glfw
    GLFWwindow * window;

    //initialisation de la lib
    bbopInit(1920, 1080,"Pacman",window);
    glfwMaximizeWindow(window);
    
    GameLoop game(window);
    std::cout << "Partie initialisée" << std::endl;

    game.run();

    return 0;
}