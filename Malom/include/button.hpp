
#ifndef button_HPP_INCLUDED
#define button_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class button : public Widget {
protected:
    bool _pressed;
    std::string _szoveg;
public:
    button(Application * parent,int x, int y, int sx, int sy, std::string szoveg);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual std::string value();
    virtual bool changedValue();
};




#endif // GOMB_HPP_INCLUDED
