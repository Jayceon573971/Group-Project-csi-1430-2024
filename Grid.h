#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "SDL_Plotter.h"

/*
 * brief The grid class represents a grid of cells.
 */
class grid {
private:
    int row, col;           ///< Number of rows and columns in the grid.
    int size;               ///< Size of each cell in the grid.
    color _color;           ///< Color of the grid lines.

public:
    /*
     * brief Constructor for the grid class.
     *
     * This constructor initializes a grid object with the specified number of rows, columns,
     * size of each cell, and color of the grid lines.
     *
     * param r Number of rows in the grid.
     * param c Number of columns in the grid.
     * param s Size of each cell in the grid.
     * param cl Color of the grid lines.
     */
    grid(int r = 20, int c = 20, int s = 50, color cl = color{});

    int getRow() const;     ///< Get the number of rows in the grid.
    int getCol() const;     ///< Get the number of columns in the grid.
    int getSize() const;    ///< Get the size of each cell in the grid.
    color getColor() const; ///< Get the color of the grid lines.

    void setRow(const int r);   ///< Set the number of rows in the grid.
    void setCol(const int c);   ///< Set the number of columns in the grid.
    void setSize(const int s);  ///< Set the size of each cell in the grid.
    void setColor(const color cl);  ///< Set the color of the grid lines.

    /*
     * brief Draw the grid on the specified SDL plotter.
     *
     * This function draws the grid lines on the specified SDL plotter object.
     *
     * param g Reference to the SDL plotter object.
     */
    void draw(SDL_Plotter& g);
};

#endif // GRID_H_INCLUDED
