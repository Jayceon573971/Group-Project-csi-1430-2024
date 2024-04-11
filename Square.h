#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "SDL_Plotter.h"
#include <ctime>

enum TYPE{EMPTY, OASIS, CACTUS, RABBIT, SNAKE, HAWK};

class square {
private:
    TYPE type;
    color _color;
    point loc;
    point prevLoc;
    int size;
    bool changed;
public:
    square();

    void setType(TYPE);
    void setColor(color);
    void setLoc(point);
    void setSize(int);

    TYPE getType() const;
    color getColor() const;
    point getLoc() const;
    int getSize() const;

    void draw(SDL_Plotter& g);
};

#endif // SQUARE_H_INCLUDED
