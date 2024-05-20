
#include "dinamicText.hpp"
#include "graphics.hpp"

using namespace genv;

dinamicText::dinamicText(Application * parent,int x, int y, int sx, int sy)
    : Widget(parent,x,y,sx,sy)
{
    _checked=false;
    _szoveg="";
    _copySzoveg=_szoveg;
}

std::string dinamicText::value()
{
    return _szoveg;
}

bool dinamicText::changedValue()
{
    if(_copySzoveg!=_szoveg)
    {
        _copySzoveg=_szoveg;
        return true;
    }
    return false;

}

void dinamicText::draw()
{
    gout << move_to(_x, _y) << color(255,255-_focused*200,255-_focused*200) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << color(255,255,255);
    //az utolso lathato karaktereket irja ki a szelessegtol fuggoen
    if (_szoveg.length()>(_size_x-10)/gout.twidth("a")){
        gout << move_to(_x+4, _y+20) << text(_szoveg.substr(_szoveg.length()-(_size_x-10)/gout.twidth("a"),_szoveg.length()));
    }
    else{
        gout << move_to(_x+4, _y+20) << text(_szoveg);
    }

//    if() {gout<< text("|");}
}

void dinamicText::handle(event ev)
{
    if(ev.type==ev_key && ev.keycode>0 && ev.keycode<=255)
    {

        if(ev.keycode>=32)
        {
            _szoveg+=ev.keycode;
            _copySzoveg=_szoveg;
        }
        if(ev.keycode==8 && _szoveg.length()>=1)
        {
            _szoveg.erase(_szoveg.length()-1, _szoveg.length()-0);
            _copySzoveg=_szoveg;
        }

        if(ev.keycode==13)
        {
            _copySzoveg="";
        }
    }
}





