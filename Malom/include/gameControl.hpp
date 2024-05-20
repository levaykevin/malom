
#ifndef GAMECONTROL_HPP_INCLUDED
#define GAMECONTROL_HPP_INCLUDED
#include <vector>

class gameControl{
protected:
    int _whichPlayer=0;

public:
    std::vector<std::vector<int> > _table{ {0,-1,-1,0,-1,-1,0},
                                 {-1,0,-1,0,-1,0,-1},
                                 {-1,-1,0,0,0,-1,-1},
                                 {0,0,0,-1,0,0,0},
                                 {-1,-1,0,0,0,-1,-1},
                                 {-1,0,-1,0,-1,0,-1},
                                 {0,-1,-1,0,-1,-1,0} };
    virtual bool canTakeFigure();
    virtual bool nearby(int x_from, int y_from, int x_to, int y_to);
    virtual void turn();
    virtual int whichPlayer();
    virtual void setInitialVector();
    virtual void tableDraw();



};

#endif // GAMECONTROL_H_INCLUDED
