
#ifndef STATICTEXT_HPP_INCLUDED
#define STATICTEXT_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class staticText : public Widget {
protected:
    std::string _szoveg;
public:
    staticText(Application * parent,int x, int y, int sx, int sy, std::string szoveg);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual bool changedValue();
    virtual std::string value();
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual bool focusable();
    virtual void addElement(std::string);
    virtual void setText(std::string);
};

#endif // STATICTEXT_HPP_INCLUDED
