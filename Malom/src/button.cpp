
#include "button.hpp"
#include "graphics.hpp"

using namespace genv;

button::button(Application * parent,int x, int y, int sx, int sy, std::string szoveg)
    : Widget(parent,x,y,sx,sy)
{
    _pressed=false;
    _szoveg=szoveg;
    _moveable=false;
}

std::string button::value()
{
    return _szoveg;
}

bool button::changedValue()
{
    return _pressed;
}

void button::draw()
{
    gout << move_to(_x, _y)
        << color(255,255-_focused*200,255-_focused*200)
        << box(_size_x, _size_y);
    gout << move_to(_x+2+_pressed*2, _y+2+_pressed*2)
        << color(0,0,0)
        << box(_size_x-4-_pressed*4, _size_y-4-_pressed*4);
    gout << color(255,255,255);
    gout << move_to(_x+4, _y+20)
        << genv::text(_szoveg);

}

void button::handle(event ev)
{
    _pressed=false;
    if(_x<=ev.pos_x && (_x+_size_x)>=ev.pos_x && _y<=ev.pos_y && (_y+_size_y)>=ev.pos_y && ev.button==btn_left){
        _pressed=true;
    }
}
