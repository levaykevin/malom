
#ifndef OPEFILETEXT_HPP_INCLUDED
#define OPEFILETEXT_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class openfileText : public Widget {
protected:
    bool _checked;
    std::string _szoveg;
public:
    openfileText(Application * parent,int x, int y, int sx, int sy);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual bool is_checked();
    virtual std::string value();
    virtual bool changedValue();
};


#endif // OPEFILETEXT_HPP_INCLUDED
