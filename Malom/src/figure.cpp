
#include "figure.hpp"
#include "graphics.hpp"
#include <math.h>

using namespace genv;

figure::figure(Application * parent,int x, int y, int sx, int sy, int whichPlayer)
    : Widget(parent,x,y,sx,sy)
{
    _whichPlayer=whichPlayer;
}


void figure::draw()
{
    if (_x>500 && _y>300)
    {
        _moveable=false;
    }
    for (int i=-18;i<=18;i++)
    {
        for (int j=-18;j<=18;j++)
        {
            if ((pow(i,2)+pow(j,2))<pow(15+_focused*2,2))
            {
                gout << move_to(_x-i, _y-j)
                    << color(100,100,100) << dot;
            }
            if ((pow(i,2)+pow(j,2))<pow(13,2))
            {
                gout << move_to(_x-i, _y-j)
                    << color(150-215*_whichPlayer,255*_whichPlayer,0) << dot;
            }
        }
    }
    gout<<move_to(_x,_y)
        <<color(255,255,255)<<box(5,5);
}

void figure::handle(event ev)
{

}


std::string figure::value()
{
    return "";
}

bool figure::changedValue()
{
    return false;
}

bool figure::moveable()
{
    return _moveable;
}

int figure::returnXcoord()
{
    return _x;
}

int figure::returnYcoord()
{
    return _y;
}

void figure::setXcoord(int x)
{
    _x=x;
}

void figure::setYcoord(int y)
{
    _y=y;
}

int figure::whichPlayer()
{
    return _whichPlayer;
}

void figure::setMoveable(bool setMoveable)
{
    _moveable=setMoveable;
}

bool figure::focusable()
{
    return _focusable;
}

void figure::changeFocusable(bool change)
{
    _focusable=change;
}
