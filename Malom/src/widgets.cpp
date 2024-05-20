
#include "widgets.hpp"
#include "graphics.hpp"
#include "application.hpp"
using namespace genv;

Widget::Widget(Application * parent,int x, int y, int sx, int sy) : _parent(parent)
{
    parent->registerWidget(this);
    _x=x;
    _y=y;
    _size_x=sx;
    _size_y=sy;
    _focused=false;
    _grabbed=false;
    _moveable=true;
}

void Widget::setfocus(bool f)
{
    _focused = f;
}

bool Widget::focusable()
{
    return true;
}

bool Widget::is_selected(int mouse_x, int mouse_y)
{
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}

bool Widget::nullValue()
{
    if (value()==""){
        return true;
    }
    return false;
}

void Widget::moveObj(int ex, int ey, int XX, int YY)
{
    if(ex-_dx>0 && ey-_dy>0 && ex-_dx<XX-_size_x && ey-_dy<YY-_size_y) {
        _x=ex-_dx;
        _y=ey-_dy;
    }
}

void Widget::catchObj(int ex, int ey)
{
    _dx=ex-_x;
    _dy=ey-_y;
    _grabbed=true;
}

void Widget::releaseObj()
{
    _grabbed=false;
}

bool Widget::insideObj(int ex, int ey)
{
    return (_x<=ex && (_x+_size_x)>=ex && _y<=ey && (_y+_size_y)>=ey);
}

bool Widget::grabbed()
{
    return _grabbed;
}

void Widget::addElement(std::string)
{

}

void Widget::removeElement(std::string)
{

}

bool Widget::moveable()
{
    return _moveable;
}

bool Widget::is_focused()
{
    return _focused;
}
