#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "SDL_Plotter.h"
class grid {
private:
    int row, col;
    int size;
    color _color;
public:
    grid(int r = 20, int c = 20, int s = 50, color cl = color{});

    int getRow() const;
    int getCol() const;
    int getSize() const;
    color getColor() const;

    void setRow(const int r);
    void setCol(const int c);
    void setSize(const int s);
    void setColor(const color cl);

    void draw(SDL_Plotter& g);
};


#endif // GRID_H_INCLUDED
