#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "SDL_Plotter.h"
#include <ctime>
#include <string>
#include <cstdlib>

enum TYPE{EMPTY, OASIS, CACTUS, RABBIT, SNAKE, HAWK, SINKHOLE};
enum SEASON {SUMMER, FALL, WINTER, SPRING};
const int SIZE = 500;
const int SIDE = 20;
const int DIM = SIZE / SIDE;


class square {
private:
    TYPE type;
    color _color;
    int row;
    int col;
    int health;
public:
    square();

    void setType(TYPE);
    void setColor(color);
    void setRow(int);
    void setCol(int);
    void setHealth(int);
    void updateHealth(int);

    TYPE getType() const;
    color getColor() const;
    int getRow() const;
    int getCol() const;
    int getHealth() const;

    void draw(SDL_Plotter& g, SEASON&);
    char scan(square[][DIM], int, int);
    int moveINX(square[][DIM], int, int);
    int moveINY(square[][DIM], int, int);
    void move(int, int);
    void kill(square[][DIM], int, int);
    void reproduce(square[][DIM], int, int);
    void reset();
    void die();
};

void allToDefault(square s[][DIM]);

#endif // SQUARE_H_INCLUDED
