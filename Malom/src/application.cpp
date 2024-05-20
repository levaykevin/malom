
#include "application.hpp"
#include "graphics.hpp"
#include "widgets.hpp"
#include <iostream>

using namespace genv;


Application::Application()
{
    _log.open("log.txt");
};

Application::~Application()
{
    _log.close();
}

void Application::event_loop(int XX, int YY) {
    event ev;
    int focus = 0;
    Widget* catched=0;
    bool rightclick=false;
    while(gin >> ev && ev.keycode!=key_escape) {
        gout<<move_to(0,0)<<color(0,0,0)<<box(XX,YY);

        _posx=ev.pos_x;
        _posy=ev.pos_y;

            action();


        for (Widget * w : widgets) {
            w->draw();
        }

        if (ev.keycode == 's'){
            _log<<"Aktualis elmentett ertekek innentol------------------"<<std::endl;
            for (Widget * w : widgets) {
                _log<<w->value()<<std::endl;
                std::cout<<w->value()<<std::endl;
            }
            _log<<"Idaig------------------------------------------------"<<std::endl;
        }

        if (focus!=-1) {
            widgets[focus]->draw();
            widgets[focus]->handle(ev);
            if (widgets[focus]->changedValue())
            {
                std::cout<<widgets[focus]->value()<<std::endl;
                _log<<"Valtozott ertek: "<<widgets[focus]->value()<<std::endl;
            }
        }



        if (ev.type==ev_mouse)
        {
            if (ev.button==-btn_right)
            {
                rightclick=false;
            }

            if (ev.button==btn_right)
            {
                catched=0;
                rightclick=true;
                for (Widget * w : widgets)
                {
                    if(w->insideObj(ev.pos_x, ev.pos_y) && w->moveable())
                    {
                        if (catched)
                            catched->releaseObj();
                        catched=w;
                    }
                    else {
                        if (w->grabbed())
                        {
                            w->releaseObj();
                        }
                    }
                }
                if (catched)
                {
                    catched->catchObj(ev.pos_x, ev.pos_y);
                }
            }
            if (rightclick && catched)
            {
                catched->moveObj(ev.pos_x, ev.pos_y, XX, YY);
            }
        }



        if (ev.keycode == key_tab){
            widgets[focus]->setfocus(false);
            ++focus%=widgets.size();

            if (!widgets[focus]->focusable()){
                ++focus%=widgets.size();
            }
            if ( widgets[focus]->focusable())
            {
                widgets[focus]->setfocus(true);
            }
        }


        if (ev.type == ev_mouse && (ev.button==btn_left || ev.button==btn_right)) {
            for (size_t i=0;i<widgets.size();i++) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    if (focus!=-1){
                        widgets[focus]->setfocus(false);
                    }
                    focus = i;
                    if ( widgets[i]->focusable())
                    {
                        widgets[i]->setfocus(true);
                    }
                }
            }
        }
        gout << refresh;
    }
}

int Application::returnXpos()
{
    return _posx;
}

int Application::returnYpos()
{
    return _posy;
}
