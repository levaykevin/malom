
#ifndef DINAMICTEXT_HPP_INCLUDED
#define DINAMICTEXT_HPP_INCLUDED
#include "graphics.hpp"
#include "widgets.hpp"

class dinamicText : public Widget {
protected:
    bool _checked;
    std::string _szoveg, _copySzoveg;
public:
    dinamicText(Application * parent,int x, int y, int sx, int sy);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual std::string value();
    virtual bool changedValue();
};

#endif // STATICTEXT_HPP_INCLUDED
