
#include "choose.hpp"
#include "graphics.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace genv;

choose::choose(Application * parent, int x, int y, int sx, int minimum, std::string fileName)
    : Widget(parent,x,y,sx,_sy)
{
    _min=minimum;
    _sy=gout.cascent()+8;
    _fileName=fileName;
    text();
    _chosenElement=0;
    _pressedArrow=false;
    _pressedScroll=false;
    _size_y=_sy;
    setElementParam();
    _row=0;
    _checkFormer=_chosenElement;
    _focusedElement=0;
}

void choose::setElementParam()
{
    if (_textout.size()>0){
        _elementLimit=_min;
        if (_textout.size()<_min){
            _elementLimit=_textout.size();
        }
        _visibleElementNumber=_textout.size()-_elementLimit;
        _chosenElement%=_textout.size();
    }
    else{
       _elementLimit=0;
       _visibleElementNumber=0;
       _chosenElement=0;
    }

}


void choose::text()
{
    _textout.push_back("alap");
    std::ifstream f(_fileName);
    std::string temp;
    while(f.good())
    {
        std::getline(f,temp);
        _textout.push_back(temp);
    }

    f.close();
}

std::string choose::value()
{
    if (_textout.size()>0){
        return _textout[_chosenElement];
    }
    return "";
}

bool choose::changedValue()
{
    if(_chosenElement!=_checkFormer)
    {
        _checkFormer=_chosenElement;
        return true;
    }
    return false;
}


bool choose::over(event ev, int x0, int x, int y0, int y)
{
    if(ev.pos_x<=x && ev.pos_x>=x0 && ev.pos_y>=y0 && ev.pos_y<=y){
        return true;
    }
    return false;
}


void choose::openText(int changeColor)
{
    gout << move_to(_x,_y+_sy*(_elementNumber-_row + 1))
        << color(255,255,255)
        << box(_size_x+2-20, _sy);
    gout << move_to(_x+1,_y+_sy*(_elementNumber-_row + 1)+1)
        << color(0+changeColor,0+changeColor,0+changeColor)
        << box(_size_x-20, _sy-2);
    gout << move_to(_x+3,_y+_sy*(_elementNumber-_row + 1)+gout.cascent()+4)
        << color(255,255,255);
    if (gout.twidth(_textout[_elementNumber])>_size_x-30){
        gout << genv::text(_textout[_elementNumber].substr(0,(_size_x-30)/gout.twidth("a")));
    }
    else{
        gout << genv::text(_textout[_elementNumber]);
    }
}


void choose::scrollDraw()
{
    /*gout << move_to(_x+_size_x,_y+_sy) << color(255,255,255) << box(-20,_size_y-_sy);
    gout << move_to(_x+_size_x-1,_y+_sy+1) << color(0,0,0) << box(-18,_size_y-_sy-2);
    gout << move_to(_x+_size_x,_y+_sy+(_size_y-_sy)/(_visibleElementNumber+1)*_row) << color(255,255,255) << box(-20,(_size_y-_sy)/(_visibleElementNumber+1));
*/
}

void choose::draw()
{

    if (!_focused) _pressedArrow=false;


    gout << move_to(_x, _y)
        << color(255,255-_focused*200,255-_focused*200)
        << box(_size_x, _sy);
    gout << move_to(_x+2, _y+2)
        << color(0,0,0)
        << box(_size_x-4, _sy-4);
    gout << move_to(_x+_size_x, _y)
        << color(255,255-_focused*200,255-_focused*200)
        << box(-20, _sy);
    gout << move_to(_x+_size_x-2, _y+2)
        << color(0,0,0)
        << box(-(20-4), _sy-4);
    gout << move_to(_x+4, _y+gout.cascent()+4)
        << color(255,255,255);

    if(_textout.size()==0){
        gout << genv::text("");
    }
    else if (gout.twidth(_textout[_chosenElement])>_size_x-30){
        gout << genv::text(_textout[_chosenElement].substr(0,(_size_x-30)/gout.twidth("a")));
    }
    else{
        gout << genv::text(_textout[_chosenElement]);
    }


    if (_pressedArrow){
        _size_y=_sy*(_elementLimit + 1);
        gout << move_to(_x+_size_x-4,_y+_sy-4)
            << color(255,255,255)
            << line(-(10-3),-(_sy-8)) << line(-(10-3),+(_sy-8));
        scrollDraw();
    }
    else if(!_pressedArrow || !_focused){
        _size_y=_sy;
        gout << move_to(_x+_size_x-4,_y+4)
            << color(255,255,255)
            << line(-(10-3),(_sy-8))
            << line(-(10-3),-(_sy-8));
    }
}

void choose::optionListDraw(event ev, int from)
{
    for (int i=from;i<_elementLimit+from;i++){
        _elementNumber=i;
        if (_pressedArrow && over(ev,_x+1, _x+1+_size_x-20, _y+_sy*(i-from + 1)+1, _y+_sy*(i-from + 1)+1+_sy-2)){
            _focusedElement=i;
            openText(100);
            if (ev.button==btn_left){
                _chosenElement=i;
                _pressedArrow=!_pressedArrow;
            }
        }
        else if (_pressedArrow){
            openText(0);
        }
    }
}

void choose::handle(event ev)
{

    if (_textout.size()!=0 && over(ev,_x+_size_x-20,_x+_size_x,_y,_y+_sy) && ev.button==btn_left){
        _pressedArrow=!_pressedArrow;
    }
    optionListDraw(ev,_row);

    if (!over(ev,_x+1, _x+1+_size_x-20, _y+_sy, _y+_size_y) && _pressedArrow){
        _elementNumber=_focusedElement;
        openText(100);
    }


    if (_row<_visibleElementNumber && ev.button==btn_wheeldown){
        _row++;
        _focusedElement++;
    }
    else if (_row>0 && ev.button==btn_wheelup){
        _row--;
        _focusedElement--;
    }

    switch (ev.keycode){
        case key_right : _pressedArrow=true;
        break;
        case key_left : _pressedArrow=false;
        break;
        case key_pgup : _focusedElement=0; _row=0;
        break;
        case key_pgdn : _focusedElement=_textout.size()-1; _row=_visibleElementNumber;
        break;
        case key_down : if (_focusedElement<_elementLimit+_row-1) _focusedElement++;
                        else if (_focusedElement<_textout.size()-1) {_row++; _focusedElement++;}
        break;
        case key_up : if (_focusedElement>0) _focusedElement--;
                      if (_focusedElement<_row && _focusedElement>=0) _row--;
        break;
        case key_enter : _chosenElement=_focusedElement;
        break;
    }


    if (over(ev, _x+_size_x-20, _x+_size_x, _y+_sy+(_size_y-_sy)/(_visibleElementNumber+1)*_row, _y+_sy+(_size_y-_sy)/(_visibleElementNumber+1)*_row+(_size_y-_sy)/(_visibleElementNumber+1)) && ev.button==btn_left){
        _pressedScroll=true;
    }
    else if(ev.button==-btn_left){
        _pressedScroll=false;
    }


    if (_pressedScroll || (ev.button==btn_left && ev.pos_x<=_x+_size_x && ev.pos_x>=_x+_size_x-20)){
        if (ev.pos_y<=_y+_sy+(_size_y-_sy)/(_visibleElementNumber+1)) _row=0;
        else if (ev.pos_y>=_y+_sy+(_size_y-_sy)/(_visibleElementNumber+1)*(_visibleElementNumber)) _row=_visibleElementNumber;
        for (int i=1;i<_visibleElementNumber;i++)
        {
            if (ev.pos_y>=_y+_sy+(_size_y-_sy)/(_visibleElementNumber+1)*i && ev.pos_y<=_y+_sy+(_size_y-_sy)/(_visibleElementNumber+1)*(i+1)){
                _row=i;
            }
            _focusedElement=_row;
        }
    }
}


void choose::addElement(std::string add)
{
    if (add!=""){
        _textout.push_back(add);
        setElementParam();
    }
}


void choose::removeElement(std::string reMove)
{
    if (_textout.size()>0){
        _textout.erase(find(_textout.begin(),_textout.end(),reMove));
        setElementParam();
    }
}


int choose::clearElement()
{
    int index=_chosenElement%_textout.size();
    _textout.clear();
    setElementParam();
    return index;
}


void choose::getIndex(int index)
{
    _chosenElement=index%_textout.size();
}
