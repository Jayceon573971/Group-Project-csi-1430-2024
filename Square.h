#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "SDL_Plotter.h"
#include <ctime>
#include <string>
#include <cstdlib>

enum TYPE{EMPTY, OASIS, CACTUS, RABBIT, SNAKE, HAWK};
const int SIZE = 500;
const int SIDE = 20;
const int DIM = SIZE / SIDE;


class square {
private:
    TYPE type;
    color _color;
    point loc;
    point prevLoc;
    int size;
    bool changed;
    int row;
    int col;
public:
    square();

    void setType(TYPE);
    void setColor(color);
    void setLoc(point);
    void setSize(int);
    void setRow(int);
    void setCol(int);

    TYPE getType() const;
    color getColor() const;
    point getLoc() const;
    int getSize() const;

    void draw(SDL_Plotter& g);
    string scan(square[][DIM], int, int);
    int moveINX(square[][DIM], int, int);
    int moveINY(square[][DIM], int, int);
    void move(int, int);
};
void allToDefault(square s[][DIM]);

#endif // SQUARE_H_INCLUDED
