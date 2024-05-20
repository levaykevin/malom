
#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include <sstream>
#include "application.hpp"
#include <iostream>
#include <fstream>
#include "counter.hpp"
#include "choose.hpp"
#include "button.hpp"
#include "staticText.hpp"
#include "figure.hpp"
#include <math.h>
#include "gameControl.hpp"

using namespace std;
using namespace genv;

int XX=800;
int YY=400;

class MyApplication : public Application
{
protected:
    int _mezoMeret = 50;
    int formerXcoord=-1;
    int formerYcoord=-1;
    int focusedIndex=-1;
    staticText * staticText1;
    staticText * staticTextPlayer;
    button * buttonNextPlayer;
    button * buttonNewGame;
    figure * figures;
    vector<figure*> _figureFirstPlayer, _figureVectorSecondPlayer, _allFigure, _stepFigureVector;
    gameControl * rules;
    bool _Focusvalt=false;
    int _xCoord=0, _yCoord=0;
public:
    MyApplication(){

//        staticText1 = new staticText(this,520,15,250,30,"Lévay Kevin - Malom");
        staticTextPlayer = new staticText(this,130,15,160,30,"1. jatekos jon");
        buttonNextPlayer = new button(this,400,130,150,30,"Kovetkezo jatekos");
        buttonNewGame = new button(this,400,170,100,30,"Uj jatek");
        rules = new gameControl();
        for (int i=0;i<9;i++)
        {
            figure * figureFirstPlayer=new figure(this,420+i*40,40,20,20,0);
            _figureFirstPlayer.push_back(figureFirstPlayer);
        }

        _allFigure=_figureFirstPlayer;

        for (int i=0;i<9;i++)
        {
            figure * figureSecondPlayer=new figure(this,420+i*40,100,20,20,1);
            _figureVectorSecondPlayer.push_back(figureSecondPlayer);
            _allFigure.push_back(figureSecondPlayer);
        }
    }

    virtual void newGame()
    {
        for (int i=0;i<9;i++)
        {
            _figureFirstPlayer[i]->setXcoord(420+i*40);
            _figureVectorSecondPlayer[i]->setXcoord(420+i*40);
            _figureFirstPlayer[i]->setYcoord(60);
            _figureVectorSecondPlayer[i]->setYcoord(100);
        }
        rules->setInitialVector();
        for (figure* f : _allFigure)
        {
            f->changeFocusable(true);
        }
        _Focusvalt=false;
        focusedIndex=-1;
        _xCoord=0;
        _yCoord=0;
    }

    virtual void fieldDraw()
    {
        for (int i=0;i<3;i++)
        {
            gout<<move_to(_mezoMeret-5+i*_mezoMeret,_mezoMeret-5+i*_mezoMeret)
                <<color(255,255,255)
                <<box_to(_mezoMeret*7+5-i*_mezoMeret,_mezoMeret*7+5-i*_mezoMeret);
            gout<<move_to(_mezoMeret+5+i*_mezoMeret,_mezoMeret+5+i*_mezoMeret)
                <<color(0,0,0)
                <<box_to(_mezoMeret*7-5-i*_mezoMeret,_mezoMeret*7-5-i*_mezoMeret);
        }

        gout<<move_to(_mezoMeret,_mezoMeret-5+3*_mezoMeret)
            <<color(255,255,255)
            <<box_to(_mezoMeret+2*_mezoMeret,_mezoMeret+5+3*_mezoMeret);
        gout<<move_to(_mezoMeret+4*_mezoMeret,_mezoMeret-5+3*_mezoMeret)
            <<color(255,255,255)
            <<box_to(_mezoMeret+6*_mezoMeret,_mezoMeret+5+3*_mezoMeret);

        gout<<move_to(_mezoMeret-5+3*_mezoMeret,_mezoMeret)
            <<color(255,255,255)
            <<box_to(_mezoMeret+5+3*_mezoMeret,_mezoMeret+2*_mezoMeret);
        gout<<move_to(_mezoMeret-5+3*_mezoMeret,_mezoMeret+4*_mezoMeret)
            <<color(255,255,255)
            <<box_to(_mezoMeret+5+3*_mezoMeret,_mezoMeret+6*_mezoMeret);

        gout<<move_to(400,300)
            <<color(255,255,255)
            <<box_to(XX-1,YY-1);
        gout<<move_to(400,295)
            <<text("Kiesett");
        gout<<move_to(410,310)
            <<color(0,0,0)
            <<box_to(XX-11,YY-11);

    }

    virtual void setCoord(int wPlayer)
    {
        bool positionReserved;
        int xCoord, yCoord;

        if (wPlayer==0)
        {
            for (figure* f : _allFigure)
            {
                f->setMoveable(true);
            }

            for (size_t i=0;i<_figureFirstPlayer.size();i++)
            {
                if (!_Focusvalt && _figureFirstPlayer[i]->is_focused())
                {
                    focusedIndex=i;
                    _Focusvalt=true;
                }
            }

            for (size_t i=0;i<_figureFirstPlayer.size();i++)
            {
                if (focusedIndex==i)
                {
                    _figureFirstPlayer[i]->setMoveable(true);
                }
            }
            _stepFigureVector=_figureFirstPlayer;
        }

        if (wPlayer==1)
        {
            for (figure* f : _allFigure)
            {
                f->setMoveable(false);
            }

            for (size_t i=0;i<_figureVectorSecondPlayer.size();i++)
            {
                if (!_Focusvalt && _figureVectorSecondPlayer[i]->is_focused())
                {
                    focusedIndex=i;
                    _Focusvalt=true;
                }
            }

            for (size_t i=0;i<_figureVectorSecondPlayer.size();i++)
            {
                if (focusedIndex==i)
                {
                    _figureVectorSecondPlayer[i]->setMoveable(true);
                }
            }
            _stepFigureVector=_figureVectorSecondPlayer;
        }

        for (figure* f : _stepFigureVector)
        {
            xCoord=round(f->returnXcoord()/_mezoMeret);
            yCoord=round(f->returnYcoord()/_mezoMeret);
            if (f->moveable())
            {
                if (xCoord>0 && xCoord<8 && yCoord>0 && yCoord<8 && !(xCoord==4 && yCoord==4))
                {
                    if (xCoord==yCoord || xCoord+yCoord==8 || xCoord==4 || yCoord==4)
                    {
                        f->setXcoord(xCoord*_mezoMeret);
                        f->setYcoord(yCoord*_mezoMeret);

                        {
                            _xCoord=xCoord;
                            _yCoord=yCoord;
                        }

                        for (figure* g : _allFigure)
                        {
                            if (f!=g && f->returnXcoord()==g->returnXcoord() && f->returnYcoord()==g->returnYcoord())
                            {
                                f->setXcoord(xCoord*_mezoMeret+20);
                                f->setYcoord(yCoord*_mezoMeret+20);
                            }
                        }
                    }
                }
            }
        }
    }


    virtual void makeStep()
    {
        setCoord(rules->whichPlayer());
        if (buttonNextPlayer->changedValue() && _xCoord-1>-1 && _yCoord>-1)
        {
            if (rules->_table[_xCoord-1][_yCoord-1]==0)
            {
                rules->_table[_xCoord-1][_yCoord-1]=rules->whichPlayer()+1;
            }
            rules->tableDraw();
            _Focusvalt=false;
            rules->turn();
            if (rules->whichPlayer()==0)
            {
                staticTextPlayer->setText("1. jatekos jon");
            }
            else
            {
                staticTextPlayer->setText("2. jatekos jon");
            }
            _xCoord=-1;
            _yCoord=-1;
        }
    }

    virtual void takeFigure()
    {
        if(rules->canTakeFigure())
        {
            cout<<"malom";
            if (rules->whichPlayer()==0)
            {
                for (figure* f : _figureVectorSecondPlayer)
                {
                    f->setMoveable(true);
                }
                for (figure* f : _figureFirstPlayer)
                {
                    f->setMoveable(false);
                }
            }
            else
            {
                for (figure* f : _figureFirstPlayer)
                {
                    f->setMoveable(true);
                }
                for (figure* f : _figureVectorSecondPlayer)
                {
                    f->setMoveable(false);
                }
            }
        }
    }

    virtual void action()
    {
        fieldDraw();
        makeStep();
        if (buttonNewGame->changedValue())
        {
            newGame();
        }

    }
};

int main()
{
    gout.open(XX, YY);
    MyApplication app;
    app.event_loop(XX, YY);
    return 0;
}

