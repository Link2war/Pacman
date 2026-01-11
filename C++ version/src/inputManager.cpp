#include "../include/inputManager.h"

InputManager::InputManager() :
    direction()
{
    
}

void InputManager::update(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        direction.x = 0;
        direction.y = -1;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        direction.x = 0;
        direction.y = 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        direction.x = -1;
        direction.y = 0;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        direction.x = 1;
        direction.y = 0;
    }
}

Vector2i InputManager::getDirection() const
{
    return direction;
}

void InputManager::reset()
{
    direction.x = 0;
    direction.y = 0;
}