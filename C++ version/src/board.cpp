#include "../include/board.h"

Board::Board()
{
    initLayout();
    initOffset();
    initTextures();
}

Board::~Board()
{
    for (int i=1; i<7; i++) {
        if (textures[i] != nullptr) {
            delete textures[i];
            textures[i] = nullptr;
        }
    }
}

void Board::initLayout() {
    int layout[BoardConstants::HEIGHT][BoardConstants::WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 6, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 5, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
        {1, 3, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 3, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 5, 2, 1, 3, 2, 2, 1, 2, 2, 3, 1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 1, 0, 1, 1, 0, 1, 1, 0, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 2, 0, 1, 0, 4, 0, 1, 0, 2, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 1, 3, 2, 2, 1, 2, 2, 3, 1, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 3, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 3, 1},
        {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 5, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    for (int i = 0; i < BoardConstants::HEIGHT; i++) {
        for (int j = 0; j < BoardConstants::WIDTH; j++) {
            table[i][j] = layout[i][j];
        }
    }
}

void Board::initOffset()
{
    int topOffset = 50;
    int bottomOffset = 50;
    // laisser 100 d'espace en haut et en bas
    int boardSizeY = BBOP_WINDOW_RESOLUTION.y - topOffset - bottomOffset;

    // laisser 50 d'espace à gauche et à droite
    int boardSizeX = BBOP_WINDOW_RESOLUTION.x - 50 - 50;

    // Le nombre de cellules sur l'axe des ordonnées vaut BoardConstants::HEIGHT et vaut BoardConstants::WIDTH sur l'axe des abscisses
    // la taille de chaque cellule vaut donc :
    int sizeCellsY = boardSizeY/BoardConstants::HEIGHT;
    int sizeCellsX = boardSizeX/BoardConstants::WIDTH;

    // On garde la taille de cellule la plus petite pour que toutes les cellules soit visible sur l'écran sans déborder
    if (sizeCellsY < sizeCellsX) {
        cellSize = sizeCellsY;
    }
    else {
        cellSize = sizeCellsX;
    }

    // offset final placée au centre de l'écran
    offset.x = (BBOP_WINDOW_RESOLUTION.x - cellSize*BoardConstants::WIDTH) / 2;
    offset.y = (BBOP_WINDOW_RESOLUTION.y - cellSize*BoardConstants::HEIGHT) / 2 + topOffset;
}

void Board::initTextures()
{
    // initialisation de toutes les textures
    textures[static_cast<int>(Tile::Empty)] = nullptr; // texture vide par défaut
    textures[static_cast<int>(Tile::Wall)] = new Sprite("assets/default/wall.bmp");
    textures[static_cast<int>(Tile::Gum)] = new Sprite("assets/default/gum.bmp");
    textures[static_cast<int>(Tile::BigGum)] = new Sprite("assets/default/bigGum.bmp");
    textures[static_cast<int>(Tile::Pakuman)] = new Sprite("assets/default/perso.bmp");
    textures[static_cast<int>(Tile::Ghost)] = new Sprite("assets/default/ghost1_0.bmp");
    textures[static_cast<int>(Tile::Cherry)] = new Sprite("assets/default/cherry.bmp");

    // redimensionne proportionnellement toutes les textures sauf Tile::Empty
    for (int i = 1; i < 7; ++i) {
        Vector2f size = textures[i]->getSize();
        size = Vector2f(cellSize / size.x * size.x, cellSize / size.y * size.y);
        textures[i]->setSize(size);
        textures[i]->setOrigin(size.x / 2, size.y / 2);
    }
}

void Board::Draw(GLint *renderUniform) const
{
    for (int i = 0; i < BoardConstants::HEIGHT; i++)
    {
        for (int j = 0; j < BoardConstants::WIDTH; j++)
        {
            Tile tile = static_cast<Tile>(table[i][j]);
            if (tile != Tile::Empty) {
                textures[table[i][j]]->setPosition(offset.x + j * cellSize, offset.y + i * cellSize);
                textures[table[i][j]]->Draw(renderUniform);
            }
        }
    }
}

void Board::updateScreenPosition()
{
    for (int i = 0; i < BoardConstants::HEIGHT; i++)
    {
        for (int j = 0; j < BoardConstants::WIDTH; j++)
        {
            Tile tile = static_cast<Tile>(table[i][j]);
            if (tile != Tile::Empty) {
                textures[table[i][j]]->setPosition(offset.x + j * cellSize, offset.y + i * cellSize);
            }
        }
    }
}

void Board::setTile(int posX, int posY, Tile tile)
{
    table[posX][posY] = static_cast<int>(tile);
}

Tile Board::getTile(int posX, int posY) const
{
    return static_cast<Tile>(table[posX][posY]);
}

Vector2i Board::getPlayerPosition() const
{
    for (int i = 0; i < BoardConstants::HEIGHT; i++)
    {
        for (int j = 0; j < BoardConstants::WIDTH; j++)
        {
            Tile tile = static_cast<Tile>(table[i][j]);
            if (tile == Tile::Pakuman) {
                return Vector2i(i, j);
            }
        }
    }
    return Vector2i(-1, -1);
}

int Board::getGhostsNumber() const
{
    int cpt=0;

    for (int i = 0; i < BoardConstants::HEIGHT; i++)
    {
        for (int j = 0; j < BoardConstants::WIDTH; j++)
        {
            Tile tile = static_cast<Tile>(table[i][j]);
            if (tile == Tile::Ghost) {
                cpt++;
            }
        }
    }

    return cpt;
}

void Board::getGhostsPosition(std::vector<Vector2i> &ghostsPosition) const
{
    for (int i = 0; i < BoardConstants::HEIGHT; i++)
    {
        for (int j = 0; j < BoardConstants::WIDTH; j++)
        {
            Tile tile = static_cast<Tile>(table[i][j]);
            if (tile == Tile::Ghost) {
                ghostsPosition.push_back(Vector2i(i, j));
            }
        }
    }
}

Vector2f Board::getOffset() const
{
    return offset;
}

int Board::getCellSize() const
{
    return cellSize;
}

void Board::reset()
{
    
}