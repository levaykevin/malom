
#include "gameControl.hpp"
#include <iostream>
#include <math.h>

bool gameControl::canTakeFigure()
{
    for (int i=0;i<7;i++)
    {
        if (i!=3 && _table[i][i]>0 && _table[i][i]==_table[3][i] && _table[i][i]==_table[6-i][i])
        {
            return true;
        }

        if (i!=3 && _table[i][i]>0 && _table[i][i]==_table[i][3] && _table[i][i]==_table[i][6-i])
        {
            return true;
        }
    }

    for (int i=0;i<5;i+=4)
    {
        if (_table[i][3]>0 && _table[i][3]== _table[i+1][3] && _table[i][3]== _table[i+2][3])
        {
            return true;
        }

        if (_table[3][i]>0 && _table[3][i]== _table[3][i+1] && _table[3][i]== _table[3][i+2])
        {
            return true;
        }
    }

    return false;
}

bool gameControl::nearby(int x_from, int y_from, int x_to, int y_to)
{
    if (x_from==x_to && abs(y_from-y_to)==abs(3-x_from))
    {
        return true;
    }

    if (y_from==y_to && abs(x_from-x_to)==abs(3-y_from))
    {
        return true;
    }
    return false;
}

void gameControl::turn()
{
    _whichPlayer++;
    _whichPlayer%=2;
}

int gameControl::whichPlayer()
{
    return _whichPlayer;
}

void gameControl::setInitialVector()
{
    std::vector<std::vector<int> > table{ {0,-1,-1,0,-1,-1,0},
                                 {-1,0,-1,0,-1,0,-1},
                                 {-1,-1,0,0,0,-1,-1},
                                 {0,0,0,-1,0,0,0},
                                 {-1,-1,0,0,0,-1,-1},
                                 {-1,0,-1,0,-1,0,-1},
                                 {0,-1,-1,0,-1,-1,0} };
    _table=table;
}

void gameControl::tableDraw()
{
    for (int i=0;i<7;i++)
    {
        for (int j=0;j<7;j++)
        {
            std::cout<<_table[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
