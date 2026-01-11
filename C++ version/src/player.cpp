#include "../include/player.h"

Player::Player(Vector2i _tilePosition, Vector2f boardOffset, int cellSize) :
    GameCharacter(_tilePosition)
{
    initSprite(boardOffset, cellSize);
}

void Player::initSprite(Vector2f boardOffset, int cellSize)
{
    updateTexture();
    Vector2f size = sprite.getSize();
    sprite.setSize(cellSize/size.x * size.x, cellSize/size.y * size.y);
    size = sprite.getSize();
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(boardOffset.x + tilePosition.y*cellSize, boardOffset.y + tilePosition.x*cellSize);
}

void Player::updateTexture()
{
    if (direction.x == -1) {
        sprite.setTexture("assets/sprites/pakuman/pakuman_2.bmp");
    }
    else if (direction.x == 1) {
        sprite.setTexture("assets/sprites/pakuman/pakuman_0.bmp");
    }
    else if (direction.y == -1) {
        sprite.setTexture("assets/sprites/pakuman/pakuman_1.bmp");
    }
    else if (direction.y == 1) {
        sprite.setTexture("assets/sprites/pakuman/pakuman_3.bmp");
    }
    else {
        sprite.setTexture("assets/sprites/pakuman/pakuman_0.bmp");
    }
}

void Player::reset()
{
    setDirection(Vector2i(0, 0));
    setTilePosition(startTilePosition);
    updateTexture();
}