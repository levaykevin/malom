
#include "staticText.hpp"
#include "graphics.hpp"

using namespace genv;

staticText::staticText(Application * parent,int x, int y, int sx, int sy, std::string szoveg)
    : Widget(parent,x,y,sx,sy)
{
    _szoveg=szoveg;
    _moveable=false;

    for (size_t i=0;i<=_szoveg.size()/((_size_x)/gout.twidth("a"));i++)
    {
        _szoveg.insert(i*((_size_x-10)/gout.twidth("a")),"\n");
        _size_y=(i+1)*(gout.cascent()+gout.cdescent())+10;
    }
}


void staticText::draw()
{
    gout << move_to(_x, _y)
        << color(255,255,255)
        << box(_size_x-10, _size_y);
    gout << move_to(_x+2, _y+2)
        << color(0,0,0)
        << box(_size_x-14, _size_y-4);
    gout << color(255,255,255);
    gout << move_to(_x+4, _y)
        << text(_szoveg);
}

void staticText::handle(event ev)
{

}

std::string staticText::value()
{
    return _szoveg;
}

bool staticText::changedValue()
{
    return false;
}

bool staticText::is_selected(int mouse_x, int mouse_y)
{
    return false;
}

bool staticText::focusable()
{
    return false;
}

void staticText::addElement(std::string add)
{
    _szoveg="\n"+add;
}

void staticText::setText(std::string add)
{
    _szoveg="\n"+add;
}





