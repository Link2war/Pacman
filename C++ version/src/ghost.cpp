#include "../include/ghost.h"

Ghost::Ghost(Vector2i _tilePosition, Vector2f boardOffset, int cellSize, GhostColor _color) :
    GameCharacter(_tilePosition),
    color(_color)
{
    initSprite(boardOffset, cellSize);
}

void Ghost::initSprite(Vector2f boardOffset, int cellSize)
{
    updateTexture();
    Vector2f size = sprite.getSize();
    sprite.setSize(cellSize/size.x * size.x, cellSize/size.y * size.y);
    size = sprite.getSize();
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(boardOffset.x + tilePosition.y*cellSize, boardOffset.y + tilePosition.x*cellSize);
}

void Ghost::updateTexture()
{
    std::string path = "assets/sprites/ghosts/ghost" + std::to_string(static_cast<int>(color));

    if (direction.x == -1) {
        path += "_2.bmp";
        sprite.setTexture(path.c_str());
    }
    else if (direction.x == 1) {
        path += "_0.bmp";
        sprite.setTexture(path.c_str());
    }
    else if (direction.y == -1) {
        path += "_1.bmp";
        sprite.setTexture(path.c_str());
    }
    else if (direction.y == 1) {
        path += "_3.bmp";
        sprite.setTexture(path.c_str());
    }
    else {
        path += "_0.bmp";
        sprite.setTexture(path.c_str());
    }
}

void Ghost::reset()
{
    setDirection(Vector2i(0, 0));
    setTilePosition(startTilePosition);
    updateTexture();
}