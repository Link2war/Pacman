#include "../include/plateau.h"
#include "../include/gestionGraphique.h"


plateau initPlateau()
{
    plateau plat = {
        .map = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,6,2,2,2,2,2,2,2,1,2,2,2,2,5,2,2,2,1},
            {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
            {1,3,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,3,1},
            {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
            {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
            {1,2,2,5,2,1,3,2,2,1,2,2,3,1,2,2,2,2,1},
            {1,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1},
            {1,1,1,1,2,1,0,0,0,0,0,0,0,1,2,1,1,1,1},
            {1,1,1,1,2,1,0,1,1,0,1,1,0,1,2,1,1,1,1},
            {1,1,1,1,2,2,0,1,0,4,0,1,0,2,2,1,1,1,1},
            {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
            {1,1,1,1,2,1,0,0,0,0,0,0,0,1,2,1,1,1,1},
            {1,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1},
            {1,2,2,2,2,1,3,2,2,1,2,2,3,1,2,2,2,2,1},
            {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
            {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
            {1,3,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,3,1},
            {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
            {1,2,2,2,2,2,2,5,2,1,2,2,2,2,2,2,2,2,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        }
    };

    return plat;
}

void affichePlateau(plateau plat, SDL_Texture* textures[], SDL_Renderer *ren){
    int i, j;
    for (i = 0; i < MAP_HEIGHT_MAX; i++) {
        for (j = 0; j < MAP_WIDHT_MAX; j++) {
            if (plat.map[i][j] == 1){
                renderTexture(textures[1], ren, j * SIZE, i * SIZE + 70, SIZE, SIZE);
            } else if (plat.map[i][j] == 2){
                renderTexture(textures[2], ren, j * SIZE, i * SIZE + 70, SIZE, SIZE);
            } else if (plat.map[i][j] == 3){
                renderTexture(textures[3], ren, j * SIZE, i * SIZE + 70, SIZE, SIZE);
            
            } else if (plat.map[i][j] == 4){
                renderTexture(textures[4], ren, j * SIZE, i * SIZE + 70, SIZE, SIZE);
            
            } else if (plat.map[i][j] == 5){
                renderTexture(textures[5], ren, j * SIZE, i * SIZE + 70, SIZE, SIZE);
            
            } else if (plat.map[i][j] == 6){
                renderTexture(textures[6], ren, j * SIZE, i * SIZE + 70, SIZE, SIZE);
            }
        }
    }
}

struct position trouvePlayer(plateau plat)
{
    struct position pos;
    for (int i=0; i<MAP_HEIGHT_MAX; i++)
    {
        for (int j=0; j<MAP_WIDHT_MAX; j++)
        {
            if(plat.map[i][j] == 6)
            {
                pos.init = "init";
                pos.x = j;
                pos.y = i;
            }
        }
    }
    return pos;
}

struct position trouveFantome(plateau plat)
{
    struct position pos;
    for (int i=0; i<MAP_HEIGHT_MAX; i++)
    {
        for (int j=0; j<MAP_WIDHT_MAX; j++)
        {
            if(plat.map[i][j] == 4)
            {
                pos.init = "init";
                pos.x = j;
                pos.y = i;
            }
        }
    }
    return pos;
}

void cheminRapide(plateau plat, char *direction)
{
    struct position posGhost = trouveFantome(plat);
    struct position posPlayer = trouvePlayer(plat);

    int fin = 0;

    if (posGhost.x == posPlayer.x)
    {
        if (posGhost.y > posPlayer.y && plat.map[posGhost.y-1][posGhost.x] != 1)
        {
            fin = 1;
            *direction = 'h';
        }
        else if (posGhost.y < posPlayer.y && plat.map[posGhost.y+1][posGhost.x] != 1)
        {
            fin = 1;
            *direction = 'b';
        }
    }

    else if (posGhost.y == posPlayer.y)
    {
        if (posGhost.x > posPlayer.x && plat.map[posGhost.y][posGhost.x-1] != 1)
        {
            fin = 1;
            *direction = 'g';
        }
        else if (posGhost.x < posPlayer.x && plat.map[posGhost.y][posGhost.x+1] != 1)
        {
            fin = 1;
            *direction = 'd';
        }
    }

    else if (posGhost.x > posPlayer.x && posGhost.y > posPlayer.y && fin != 1)
    {
        if (posGhost.x - posPlayer.x > posGhost.y - posPlayer.y && plat.map[posGhost.y-1][posGhost.x] != 1)
        {
            fin = 1;
            *direction = 'h';
        }
        else if (plat.map[posGhost.y][posGhost.x-1] != 1)
        {
            fin = 1;
            *direction = 'g';
        }            
    }

    else if (posGhost.x > posPlayer.x && posGhost.y < posPlayer.y && fin != 1)
    {
        if (posPlayer.x - posGhost.x > posPlayer.y - posGhost.y && plat.map[posGhost.y+1][posGhost.x] != 1)
        {
            fin = 1;
            *direction = 'b';
        }
        else if (plat.map[posGhost.y][posGhost.x-1] != 1)
        {
            fin = 1;
            *direction = 'g';
        }   
    }

    else if (posGhost.x < posPlayer.x && posGhost.y < posPlayer.y && fin != 1)
    {
        if (posPlayer.x - posGhost.x > posPlayer.y - posGhost.y && plat.map[posGhost.y+1][posGhost.x] != 1)
        {
            fin = 1;
            *direction = 'b';
        }
        else if (plat.map[posGhost.y][posGhost.x+1] != 1)
        {
            fin = 1;
            *direction = 'd';
        }   
    }

    else if (posGhost.x < posPlayer.x && posGhost.y > posPlayer.y && fin != 1)
    {
        if (posPlayer.x - posGhost.x > posGhost.y - posPlayer.y && plat.map[posGhost.y-1][posGhost.x] != 1)
        {
            fin = 1;
            *direction = 'h';
        }
        else if (plat.map[posGhost.y][posGhost.x+1] != 1)
        {
            fin = 1;
            *direction = 'd';
        }   
    }
}

plateau moveFantome(plateau plat, char *direction, int start)
{
    struct position posGhost = trouveFantome(plat);
    struct position posPlayer = trouvePlayer(plat);

    cheminRapide(plat, direction);

    if (start == 1)
    {
        *direction = 'h';
        plat.map[posGhost.y][posGhost.x] = 0;
        plat.map[posGhost.y-1][posGhost.x] = 4;
    }

    else if (*direction == 'h')
    {
        if (plat.map[posGhost.y-1][posGhost.x] != 1)
        {
            plat.map[posGhost.y][posGhost.x] = 0;
            plat.map[posGhost.y-1][posGhost.x] = 4;
        }
        else
        {
            if (plat.map[posGhost.y][posGhost.x-1] != 1)
            {
                *direction = 'g';
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y][posGhost.x-1] = 4;
            }
            else if (plat.map[posGhost.y][posGhost.x+1] != 1)
            {
                *direction = 'd';
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y][posGhost.x+1] = 4;
            }
        }
    }
    else if (*direction == 'b')
    {
        if (plat.map[posGhost.y+1][posGhost.x] != 1)
        {
            plat.map[posGhost.y][posGhost.x] = 0;
            plat.map[posGhost.y+1][posGhost.x] = 4;
        }
        else
        {
            if (plat.map[posGhost.y][posGhost.x-1] != 1)
            {
                *direction = 'g';
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y][posGhost.x-1] = 4;
            }
            else if (plat.map[posGhost.y][posGhost.x+1] != 1)
            {
                *direction = 'd';
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y][posGhost.x+1] = 4;
            }
        }
    }
    else if (*direction == 'g')
    {
        if (plat.map[posGhost.y][posGhost.x-1] != 1)
        {
            plat.map[posGhost.y][posGhost.x] = 0;
            plat.map[posGhost.y][posGhost.x-1] = 4;
        }
        else
        {
            if (plat.map[posGhost.y-1][posGhost.x] != 1)
            {
                *direction = 'h';
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y-1][posGhost.x] = 4;
            }
            else if (plat.map[posGhost.y+1][posGhost.x] != 1)
            {
                *direction = 'b';
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y+1][posGhost.x] = 4;
            }
        }
    }
    else if (*direction == 'd')
    {
        if (plat.map[posGhost.y][posGhost.x+1] != 1)
        {
            plat.map[posGhost.y][posGhost.x] = 0;
            plat.map[posGhost.y][posGhost.x+1] = 4;
        }
        else
        {
            if (plat.map[posGhost.y-1][posGhost.x] != 1)
            {
                *direction = 'h';
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y-1][posGhost.x] = 4;
            }
            else if (plat.map[posGhost.y+1][posGhost.x] != 1)
            {
                *direction = 'b';   
                plat.map[posGhost.y][posGhost.x] = 0;
                plat.map[posGhost.y+1][posGhost.x] = 4;
            }
        }
    }

    return plat;
}

int addPoint(plateau plat, int x, int y)
{
    if (plat.map[y][x] == 2)
    {
        return 10;
    }
    if (plat.map[y][x] == 3)
    {
        return 50;
    }
}

plateau movePlayer(plateau plat, int x, int y, int * score)
{
    struct position pos = trouvePlayer(plat);
    
    if (x == 1)
    {
        if (plat.map[pos.y][pos.x+1] != 1)
        {
            *score += addPoint(plat, pos.x+1, pos.y);
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y][pos.x+1] = 6;
        }
    }
    else if (x == -1)
    {
        if (plat.map[pos.y][pos.x-1] != 1)
        {
            *score += addPoint(plat, pos.x-1, pos.y);
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y][pos.x-1] = 6;
        }
    }
    else if (y == 1)
    {
        if (plat.map[pos.y+1][pos.x] != 1)
        {
            *score += addPoint(plat, pos.x, pos.y+1);
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y+1][pos.x] = 6;
        }
    }
    else if (y == -1)
    {
        if (plat.map[pos.y-1][pos.x] != 1)
        {
            *score += addPoint(plat, pos.x, pos.y-1);
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y-1][pos.x] = 6;
        }
    }

    return plat;
}