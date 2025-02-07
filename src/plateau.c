#include "plateau.h"
#include "gestionGraphique.h"


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
                renderTexture(textures[1], ren, j * SIZE, i * SIZE, SIZE, SIZE);
            } else if (plat.map[i][j] == 2){
                renderTexture(textures[2], ren, j * SIZE, i * SIZE, SIZE, SIZE);
            } else if (plat.map[i][j] == 3){
                renderTexture(textures[3], ren, j * SIZE, i * SIZE, SIZE, SIZE);
            
            } else if (plat.map[i][j] == 4){
                renderTexture(textures[4], ren, j * SIZE, i * SIZE, SIZE, SIZE);
            
            } else if (plat.map[i][j] == 5){
                renderTexture(textures[5], ren, j * SIZE, i * SIZE, SIZE, SIZE);
            
            } else if (plat.map[i][j] == 6){
                renderTexture(textures[6], ren, j * SIZE, i * SIZE, SIZE, SIZE);
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
                pos.x = j;
                pos.y = i;
            }
        }
    }
    return pos;
}

plateau moveFantome(plateau plat, char *direction)
{
    struct position pos = trouveFantome(plat);

    
    srand(time(NULL));
    int nb = rand()%2;
    
    if (*direction == 'h' || *direction == 'b')
    {
        // si le fantome n'a pas encore atteind un mur
        if (*direction == 'h' && plat.map[pos.y-1][pos.x] != 1 )
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y-1][pos.x] = 4;
        }
        else if (*direction == 'b' && plat.map[pos.y+1][pos.x] != 1)
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y+1][pos.x] = 4;
        }
        
        // si le fantome a atteind un mur
        else if (plat.map[pos.y-1][pos.x] == 1 || plat.map[pos.y+1][pos.x] == 1)
        {
            if (plat.map[pos.y][pos.x+1] != 1 && plat.map[pos.y][pos.x-1] != 1)
            {
                if (nb == 0) 
                {
                    plat.map[pos.y][pos.x] = 0;
                    plat.map[pos.y][pos.x+1] = 4;
                    *direction = 'd';
                }
                else 
                {
                    plat.map[pos.y][pos.x-1] = 4;
                    plat.map[pos.y][pos.x] = 0;
                    *direction = 'g';
                }
            }
            else if (plat.map[pos.y][pos.x+1] != 1)
            {
                plat.map[pos.y][pos.x+1] = 4;
                plat.map[pos.y][pos.x] = 0;
                *direction = 'd';
            }
            else
            {
                plat.map[pos.y][pos.x-1] = 4;
                plat.map[pos.y][pos.x] = 0;
                *direction = 'g';
            }
        }
    }
    else if (*direction == 'g' || *direction == 'd')
    {
        // si le fantome n'a pas encore atteind un mur
        if (*direction == 'g' && plat.map[pos.y][pos.x-1] != 1 )
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y][pos.x-1] = 4;
        }
        else if (*direction == 'd' && plat.map[pos.y][pos.x+1] != 1)
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y][pos.x+1] = 4;
        }

        // si le fantome a atteind un mur
        if (plat.map[pos.y][pos.x+1] == 1 || plat.map[pos.y][pos.x-1] == 1)
        {
            if (plat.map[pos.y+1][pos.x] != 1 && plat.map[pos.y-1][pos.x] != 1)
            {
                if (nb == 0)
                {
                    plat.map[pos.y][pos.x] = 0;
                    plat.map[pos.y+1][pos.x] = 4;
                    *direction = 'b';
                }
                else 
                {
                    plat.map[pos.y][pos.x] = 0;
                    plat.map[pos.y-1][pos.x] = 4;
                    *direction = 'h';
                }
            }
            else if (plat.map[pos.y+1][pos.x] != 1)
            {
                plat.map[pos.y][pos.x] = 0;
                plat.map[pos.y+1][pos.x] = 4;
                *direction = 'b';
            }
            else
            {
                plat.map[pos.y][pos.x] = 0;
                plat.map[pos.y-1][pos.x] = 4;
                *direction = 'h';
            }
        }
    }

    return plat;
}

plateau movePlayer(plateau plat, int x, int y)
{
    struct position pos = trouvePlayer(plat);
    
    if (x == 1)
    {
        if (plat.map[pos.y][pos.x+1] != 1)
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y][pos.x+1] = 6;
        }
    }
    else if (x == -1)
    {
        if (plat.map[pos.y][pos.x-1] != 1)
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y][pos.x-1] = 6;
        }
    }
    else if (y == 1)
    {
        if (plat.map[pos.y+1][pos.x] != 1)
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y+1][pos.x] = 6;
        }
    }
    else if (y == -1)
    {
        if (plat.map[pos.y-1][pos.x] != 1)
        {
            plat.map[pos.y][pos.x] = 0;
            plat.map[pos.y-1][pos.x] = 6;
        }
    }

    return plat;
}