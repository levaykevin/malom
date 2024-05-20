
#ifndef FIGURE_HPP_INCLUDED
#define FIGURE_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class figure : public Widget {
protected:
    int _whichPlayer;
    bool _focusable=true;
public:
    figure(Application * parent,int x, int y, int sx, int sy, int whichPlayer);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual bool changedValue();
    virtual std::string value();
    virtual bool moveable();
    virtual int returnXcoord();
    virtual int returnYcoord();
    virtual void setXcoord(int x);
    virtual void setYcoord(int y);
    virtual int whichPlayer();
    virtual void setMoveable(bool setMoveable);
    virtual bool focusable();
    virtual void changeFocusable(bool change);
};


#endif // FIGURE_H_INCLUDED
