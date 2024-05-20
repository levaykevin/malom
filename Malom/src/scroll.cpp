
#include "scroll.hpp"
#include "graphics.hpp"
#include <fstream>
#include <vector>
#include <iostream>

using namespace genv;

scroll::scroll(Application * parent,int x, int y, int sx, int sy, std::string szoveg)
    : Widget(parent,x,y,sx,sy)
{
    _checked=false;
   _szoveg=szoveg;
   text();
   _row=0;
   _pressed=false;
   _visibleElementNumber=_textout.size()-_size_y/gout.cascent()+1;
   _pressedScroll=false;
}

void scroll::text()
{
    std::ifstream f(_szoveg);
    std::string temp;
    while(f.good())
    {
        std::getline(f,temp);
        if (gout.twidth(temp)>_size_x-30){
            _textout.push_back(temp.substr(0,(_size_x-30)/gout.twidth("a")));
            _textout.push_back(temp.substr((_size_x-30)/gout.twidth("a"),temp.size()-2));
        }
        else{
            _textout.push_back(temp);
        }
    }

    f.close();
}

std::string scroll::value()
{

}

bool scroll::changedValue()
{
    return false;
}

void scroll::scrollDraw()
{
    gout << move_to(_x+_size_x,_y) << color(255,255-_focused*200,255-_focused*200) << box(-20,_size_y);
    gout << move_to(_x+_size_x-2,_y+2) << color(0,0,0) << box(-16,_size_y-4);
    gout << move_to(_x+_size_x,_y+(_size_y)/(_visibleElementNumber+1)*_row) << color(255,255-_focused*200,255-_focused*200) << box(-20,(_size_y)/(_visibleElementNumber+1));
}

bool scroll::over(event ev, int x0, int x, int y0, int y)
{
    if(ev.pos_x<=x && ev.pos_x>=x0 && ev.pos_y>=y0 && ev.pos_y<=y) {
        return true;
    }
    return false;
}

void scroll::draw()
{
    gout << move_to(_x, _y) << color(255,255-_focused*200,255-_focused*200) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << color(255,255,255);
    //gout << move_to(_x+_size_x-2,_y+gout.cascent()/2+_row*gout.cascent())<<box(-10,10);
    gout << move_to(_x+4, _y+20);
    for (int i=_row;i<_row+_size_y/gout.cascent()-1;i++)
    {
        gout<<move_to(_x+4, _y+20+(i-_row)*gout.cascent());
        gout<<genv::text(_textout[i]);
    }
    scrollDraw();
}

void scroll::handle(event ev)
{
    if(_row<=_textout.size()-_size_y/gout.cascent() && (ev.type==ev_key && ev.keycode==key_down || ev.button==btn_wheeldown))
    {
        _row++;
    }
     if(_row>0 && (ev.type==ev_key && ev.keycode==key_up || ev.button==btn_wheelup))
    {
        _row--;
    }
    if(ev.type==ev_key && ev.keycode==key_pgup)
    {
        _row=0;
    }
    if(ev.type==ev_key && ev.keycode==key_pgdn)
    {
        _row=_textout.size()-_size_y/genv::gout.cascent()+1;
    }
    if(ev.button==btn_left && touched(ev))
    {
        _pressed=true;
    }
    if(ev.button==-btn_left)
    {
        _pressed=false;
    }
    ///hazi sortores tobb sorba, ahova kattintok oda kell ugrani

    //ha az eger a gorgo felett kattintva van akkor "megfogja" a gorgot ameddig nem engedi el a lenyomast
    if (over(ev, _x+_size_x-20, _x+_size_x, _y+(_size_y)/(_visibleElementNumber+1)*_row, _y+(_size_y)/(_visibleElementNumber+1)*_row+(_size_y)/(_visibleElementNumber+1)) && ev.button==btn_left){
        _pressedScroll=true;
    }
    else if(ev.button==-btn_left){
        _pressedScroll=false;
    }

    //a lenyomott bal eger helyzete szerint mozog a gorgo, ha az eger a gorgo felett volt akitvalva vagy a gorgore kattintott reszre ugrik a csuszka
    if (_pressedScroll || (ev.button==btn_left && ev.pos_x<=_x+_size_x && ev.pos_x>=_x+_size_x-20)){
        if (ev.pos_y<=_y+(_size_y)/(_visibleElementNumber+1)) _row=0;
        else if (ev.pos_y>=_y+(_size_y)/(_visibleElementNumber+1)*(_visibleElementNumber)) _row=_visibleElementNumber;
        for (int i=1;i<_visibleElementNumber;i++)
        {
            if (ev.pos_y>=_y+(_size_y)/(_visibleElementNumber+1)*i && ev.pos_y<=_y+(_size_y)/(_visibleElementNumber+1)*(i+1)){
                _row=i;
            }
        }
    }
}

bool scroll::touched(event ev)
{
    if (ev.pos_x>_x+_size_x-12 && ev.pos_x<_x+_size_x-2 && ev.pos_y>_y+gout.cascent()/2+_row*gout.cascent() && ev.pos_y<_y+gout.cascent()/2+_row*gout.cascent()+10)
    {
        return true;
    }
    return false;
}
