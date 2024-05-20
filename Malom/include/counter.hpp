
#ifndef COUNTER_HPP_INCLUDED
#define COUNTER_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"

class counter : public Widget {
protected:
    int _number;
    int _min, _max;
    int _sx, _sy;
    int _checkFormer;
    std::string _changeValue;
    bool _canWrite;
public:
    counter(Application * parent, int x, int y, int _min, int _max);
    virtual void draw() ;
    virtual void handle(genv::event ev);
    virtual bool upArrow(genv::event ev);
    virtual bool downArrow(genv::event ev);
    virtual std::string value();
    virtual bool changedValue();
    virtual bool overTheBox(genv::event ev);
    virtual void writeInTheBox(genv::event ev);
    virtual int strintToIntConverter(std::string input);
    virtual std::string intToStringConverter(int input);
};


#endif // COUNTER_H_INCLUDED
