
#include "counter.hpp"
#include "graphics.hpp"
#include <sstream>
#include <iostream>

using namespace genv;

counter::counter(Application * parent,int x, int y, int minimum, int maximum)
    : Widget(parent,x,y,_sx,_sy)
{
    _size_x=80;
    _size_y=30;
    _number=minimum;
    _min=minimum;
    _max=maximum;
    _checkFormer=_number;
    _changeValue="";
    _canWrite=false;
}


std::string counter::value()
{
    return intToStringConverter(_number);
}

bool counter::changedValue()
{
    if(_number!=_checkFormer && !_canWrite)
    {
        _checkFormer=_number;
        return true;
    }
    return false;
}


void counter::draw()
{

    if(!_focused) _canWrite=false;

    gout << move_to(_x, _y)
        << color(255,255-_focused*200,255-_focused*200)
        << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2)
        << color(_canWrite*100,_canWrite*100,_canWrite*100)
        << box(_size_x-4, _size_y-4);

    gout << move_to(_x+_size_x,_y)
        << color(255,255-_focused*200,255-_focused*200)
        << box(-20,_size_y/2);
    gout << move_to(_x-2+_size_x, _y+2)
        << color(0,0,0)
        << box(-(20-4), _size_y/2-4);
    gout << move_to(_x+_size_x-3,_y+_size_y/2-4)
        << color(255,255,255)
        << line(-(10-3),-(_size_y/2-8))
        << line(-(10-3),+(_size_y/2-8));

    gout << move_to(_x+_size_x,_y+_size_y/2)
        << color(255,255-_focused*200,255-_focused*200)
        << box(-20,_size_y/2);
    gout << move_to(_x+_size_x-2,_y+_size_y/2+2)
        << color(0,0,0)
        << box(-(20-4), _size_y/2-4);
    gout << move_to(_x+_size_x-3,_y+_size_y/2+4)
        << color(255,255,255)
        << line(-(10-3),_size_y/2-8)
        << line(-(10-3),-(_size_y/2-8));

    gout << color(255,255,255);

    _changeValue=intToStringConverter(_number);
    gout << move_to(_x+4, _y+20)
        << text((_changeValue));
}

void counter::handle(event ev)
{
    _changeValue=intToStringConverter(_number);

    switch (ev.keycode){
        case key_up : if(_number<_max) _number++;
        break;
        case key_down : if(_number>_min) _number--;
        break;
        case key_pgup : if(_number<=_max-10) _number+=10;
        break;
        case key_pgdn : if(_number>=_min+10) _number-=10;
        break;
    }


    switch (ev.button){
        case btn_wheelup : if(_number<_max) _number++;
        break;
        case btn_wheeldown : if(_number>_min) _number--;
        break;
        case btn_left : if(upArrow(ev) && _number<_max)  _number++;
                        if(downArrow(ev) && _number>_min) _number--;
        break;
    }


    if (overTheBox(ev) && ev.button==btn_left){
        _canWrite=true;
    }
    else if(ev.keycode==key_enter || (!overTheBox(ev) && ev.button==btn_left)){
        _canWrite=false;

        if(_changeValue=="") _changeValue="0";

        if(_number>_max) {_number=_max; _changeValue=intToStringConverter(_max);}
        if(_number<_min) {_number=_min; _changeValue=intToStringConverter(_min);}
    }
    if (_canWrite){
        writeInTheBox(ev);
    }
}


bool counter::upArrow(event ev)
{
    if(ev.pos_x<=_x+_size_x && ev.pos_x>=_x+_size_x-20 && ev.pos_y>=_y && ev.pos_y<=_y+_size_y/2){
        return true;
    }
    return false;
}


bool counter::downArrow(event ev)
{
    if(ev.pos_x<=_x+_size_x && ev.pos_x>=_x+_size_x-20 && ev.pos_y>=_y+_size_y/2 && ev.pos_y<=_y+_size_y){
        return true;
    }
    return false;
}


bool counter::overTheBox(event ev)
{
    if(ev.pos_x>=_x && ev.pos_x<=_x+_size_x-20 && ev.pos_y>=_y && ev.pos_y<=_y+_size_y){
        return true;
    }
    return false;
}


void counter::writeInTheBox(event ev)
{
    _changeValue=intToStringConverter(_number);
    if(ev.type==ev_key && ev.keycode>0 && ev.keycode<=255){
        if(ev.keycode>=32){
            _changeValue+=ev.keycode;
        }
        if(ev.keycode==8 && _changeValue.length()>0){
            _changeValue=_changeValue.substr(0,_changeValue.length()-1);
        }
    }
    _number=strintToIntConverter(_changeValue);
    if(_changeValue.length()==0){
        _number=0;
    }
}


int counter::strintToIntConverter(std::string input)
{
    int temp;
    std::istringstream iss (input);
    iss >> temp;
    return temp;
}
std::string counter::intToStringConverter(int input)
{
    std::string temp;
    std::stringstream ss;
    ss<<input;
    ss>>temp;
    return temp;
}
