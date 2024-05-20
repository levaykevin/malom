
#include "openfileText.hpp"
#include "graphics.hpp"
#include <fstream>

using namespace genv;

openfileText::openfileText(Application * parent,int x, int y, int sx, int sy)
    : Widget(parent,x,y,sx,sy)
{
    _checked=false;
    _szoveg="";
}

bool openfileText::changedValue()
{
    return false;
}

std::string openfileText::value()
{
    return _szoveg;
}

void openfileText::draw()
{
    gout << move_to(_x, _y)
        << color(255,255-_focused*200,255-_focused*200)
        << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2)
        << color(0,0,0)
        << box(_size_x-4, _size_y-4);
    gout << color(255,255,255);
    gout << move_to(_x+4, _y+20)
        << text(_szoveg);
}

void openfileText::handle(event ev)
{
    if(ev.type==ev_key && ev.keycode>0 && ev.keycode<=255)
    {
        if(ev.keycode>=32)
        {
            _szoveg+=ev.keycode;
        }
        if(ev.keycode==8 && _szoveg.length()>=1)
        {
            _szoveg.erase(_szoveg.length()-1, _szoveg.length()-0);
        }
    }
}
bool openfileText::is_checked()
{
    return _checked;
}
