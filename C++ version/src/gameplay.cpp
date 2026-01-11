#include "../include/gameplay.h"

#include <iostream>
#include <random>


Gameplay::Gameplay() :
    scene(),
    state(GameState::Playing),
    board(),
    inputManager(),
    scoreManager(),
    player(Player(board.getPlayerPosition(), board.getOffset(), board.getCellSize())),
    font(Font(30, "assets/font/DejaVuSans-Bold.ttf")),
    textScore(TexteBox("0", &font)),
    deltaTime(0),
    delay(FRAME_DELAY),
    timer(0),
    lastFrame(glfwGetTime())
{
    initTextScore();  
    initPlayer();
    initGhosts();

}

void Gameplay::initTextScore()
{
    Vector2f offset = board.getOffset();
    textScore.setPosition(Vector2f(offset.x + textScore.getSize().x/2, (offset.y + textScore.getSize().y)/2));
    textScore.setColor(Vector3i(255, 255, 255));  
}

void Gameplay::initPlayer()
{
    // supprime le pakuman (player) du plateau après avoir était transmis au Player
    Vector2i pos = board.getPlayerPosition();
    board.setTile(pos.x, pos.y, Tile::Empty); 
}

void Gameplay::initGhosts()
{
    std::vector<Vector2i> ghostsPosition;
    board.getGhostsPosition(ghostsPosition);

    for (long unsigned int i=0; board.getGhostsNumber(); i++) {
        Ghost ghost(ghostsPosition[i], board.getOffset(), board.getCellSize(), static_cast<GhostColor>(i));
        ghosts.push_back(ghost);
        board.setTile(ghostsPosition[i].x, ghostsPosition[i].y, Tile::Empty); 
    }
}

Gameplay::~Gameplay()
{

}

void Gameplay::update(GLFWwindow* window)
{
    updateDeltaTime();
    updateTimer();

    inputManager.update(window);

    if (timer >= delay) {
        updatePlayer();
        if (ghostCaughtPlayer()) {
            handleGameOver();
            return;
        }
        updateGhosts();
        if (ghostCaughtPlayer()) {
            handleGameOver();
            return;
        }
        // si plus aucun fruit victoire
        timer = 0;
    }

    updateTextBox();
}

void Gameplay::Draw()
{
    scene.Use();
    
    scene.Draw(board);
    if (!ghostCaughtPlayer()) scene.Draw(player);
    for (long unsigned int i=0; i< ghosts.size(); i++) {
        scene.Draw(ghosts[i]);
    }
    scene.Draw(textScore);
    scene.render();
}

void Gameplay::updateDeltaTime()
{
    double currentFrame = glfwGetTime();
    deltaTime = static_cast<float>(currentFrame - lastFrame);
    lastFrame = currentFrame;

    // Limiter deltaTime pour éviter les gros sauts si le jeu a été mis en pause
    if (deltaTime > 0.1f) deltaTime = 0.1f;
}

void Gameplay::updateTimer()
{
    timer += deltaTime;
}

void Gameplay::updateTextBox()
{
    std::string text = std::to_string(scoreManager.getScore());
    textScore.setTexte(text.c_str());
}

void Gameplay::updatePlayerDirection()
{
    Vector2i nextDirection = inputManager.getDirection();
    Vector2i tilePosition = player.getTilePosition();

    // on additionne la position.x avec direction.y parce que la position est inversé (logique du plateau)
    Vector2i nextTilePosition = Vector2i(tilePosition.x + nextDirection.y, tilePosition.y + nextDirection.x);

    if (board.getTile(nextTilePosition.x, nextTilePosition.y) != Tile::Wall) {
        player.setDirection(nextDirection);
    }
}

void Gameplay::updatePlayerPosition()
{
    Vector2i tilePosition = player.getTilePosition();
    Vector2i direction = player.getDirection();

    // on additionne la position.x avec direction.y parce que la position est inversé (logique du plateau)
    Vector2i nextTilePosition = Vector2i(tilePosition.x + direction.y, tilePosition.y + direction.x);

    if (board.getTile(nextTilePosition.x, nextTilePosition.y) != Tile::Wall) {
        player.setTilePosition(nextTilePosition);
        player.updateScreenPosition(board.getOffset(), board.getCellSize());
    }
}

void Gameplay::updatePlayer()
{
    updatePlayerDirection();
    updatePlayerPosition();
    player.updateTexture();

    Vector2i pos = player.getTilePosition();
    Tile tile = static_cast<Tile>(board.getTile(pos.x, pos.y));

    switch (tile)
    {
        case Tile::Gum :
            scoreManager.addGum();
            board.setTile(pos.x, pos.y, Tile::Empty);
            break;

        case Tile::BigGum :
            scoreManager.addBigGum();
            board.setTile(pos.x, pos.y, Tile::Empty);
            break;

        case Tile::Cherry :
            scoreManager.addCherry();
            board.setTile(pos.x, pos.y, Tile::Empty);
            break;

        default:
            break;
    }
}

void Gameplay::updateGhosts()
{
    for (long unsigned int i=0; i<ghosts.size(); i++) 
    {
        updateGhostDirection(ghosts[i]);
        updateGhostPosition(ghosts[i]);
        ghosts[i].updateTexture();
    }
}
void Gameplay::updateGhostDirection(Ghost& ghost)
{
    static std::mt19937 gen(std::random_device{}());

    Vector2i currentDir = ghost.getDirection();
    Vector2i tilePos = ghost.getTilePosition();

    std::vector<Vector2i> directions = {
        {1, 0}, // droite
        {-1, 0}, // gauche
        {0, 1}, // bas
        {0, -1} // haut
    };

    // évite de revenir en arrière
    Vector2i oppositeDir = {-currentDir.x, -currentDir.y};

    std::vector<Vector2i> validDirs;
    for (auto& dir : directions) {
        if (dir.x != oppositeDir.x || dir.y != oppositeDir.y) {
            Vector2i nextPos(tilePos.x + dir.y, tilePos.y + dir.x); // selon logique plateau
            if (board.getTile(nextPos.x, nextPos.y) != Tile::Wall) {
                validDirs.push_back(dir);
            }
        }
    }

    if (!validDirs.empty()) { // choisis aléatoirement l'une des direction possible
        std::uniform_int_distribution<> distrib(0, validDirs.size() - 1);
        ghost.setDirection(validDirs[distrib(gen)]);
    }
    else { // seul direction possible
        ghost.setDirection(oppositeDir);
    }
}

void Gameplay::updateGhostPosition(Ghost& ghost)
{
    Vector2i tilePosition = ghost.getTilePosition();
    Vector2i direction = ghost.getDirection();

    // on additionne la position.x avec direction.y parce que la position est inversé (logique du plateau)
    Vector2i nextTilePosition = Vector2i(tilePosition.x + direction.y, tilePosition.y + direction.x);

    if (board.getTile(nextTilePosition.x, nextTilePosition.y) != Tile::Wall) {
        ghost.setTilePosition(nextTilePosition);
        ghost.updateScreenPosition(board.getOffset(), board.getCellSize());
    }
}

void Gameplay::handleGameOver()
{
    state = GameState::GameOver;
}

void Gameplay::handleVictory()
{
    state = GameState::Victory;
}

bool Gameplay::ghostCaughtPlayer()
{
    for (long unsigned int i=0; i<ghosts.size(); i++) 
    {
        Vector2i ghostPos = ghosts[i].getTilePosition();
        Vector2i playerPos = player.getTilePosition();
        if (ghostPos.x == playerPos.x && ghostPos.y == playerPos.y) {
            return true;
        }
    }
    

    return false;
}

void Gameplay::restart()
{
    state = GameState::Playing;
    timer = 0; 
    
}