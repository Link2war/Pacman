#include "../include/gameCharacter.h"


GameCharacter::GameCharacter(Vector2i _startTilePosition) : 
    sprite(),
    startTilePosition(_startTilePosition),
    tilePosition(_startTilePosition), 
    direction(0, 0) 
{

}

void GameCharacter::Draw(GLint* renderUniform) const 
{
    sprite.Draw(renderUniform);
}

void GameCharacter::setTilePosition(Vector2i newTilePosition) 
{
    tilePosition = newTilePosition;
}

Vector2i GameCharacter::getTilePosition() const 
{
    return tilePosition;
}
    
void GameCharacter::setDirection(Vector2i newDirection) 
{
    direction = newDirection;
}

Vector2i GameCharacter::getDirection() const 
{
    return direction;
}

void GameCharacter::updateScreenPosition(Vector2f boardOffset, int cellSize) 
{
    sprite.setPosition(
        boardOffset.x + tilePosition.y * cellSize,
        boardOffset.y + tilePosition.x * cellSize
    );
}

void GameCharacter::reset()
{
    setTilePosition(startTilePosition);
    setDirection(Vector2i(0, 0));
}