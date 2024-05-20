
#ifndef CHOOSE_HPP_INCLUDED
#define CHOOSE_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>

class choose : public Widget {
protected:
    int _min;
    int _sy;
    bool _pressedArrow, _pressedScroll;
    std::string _fileName;
    std::vector<std::string> _textout;
    int _chosenElement, _elementNumber, _elementLimit, _row, _visibleElementNumber, _checkFormer, _focusedElement;
public:
    choose(Application * parent, int x, int y, int sx, int _min, std::string fileName);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void text();
    virtual void openText(int changeColor);
    virtual bool over(genv::event ev, int x0, int x, int y0, int y);
    virtual void scrollDraw();
    virtual void optionListDraw(genv::event ev, int from);
    virtual std::string value();
    virtual bool changedValue();
    virtual void addElement(std::string);
    virtual void removeElement(std::string);
    virtual int clearElement();
    virtual void getIndex(int index);
    virtual void setElementParam();

};

#endif // CHOOSE_H_INCLUDED
