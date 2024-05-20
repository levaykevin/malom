
#ifndef SCROLL_HPP_INCLUDED
#define SCROLL_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>


class scroll : public Widget {
protected:
    bool _checked, _pressed, _pressedScroll;
    std::string _szoveg;
    std::vector<std::string> _textout;
    int _row, _visibleElementNumber;
public:
    scroll(Application * parent,int x, int y, int sx, int sy, std::string szoveg);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual std::string value();
    virtual void text();
    virtual bool touched(genv::event ev);
    virtual bool changedValue();
    virtual void scrollDraw();
    virtual bool over(genv::event ev, int x0, int x, int y0, int y);
};

#endif // SCROLL_HPP_INCLUDED
