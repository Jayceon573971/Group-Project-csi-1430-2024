/*
* Authors: Colin Strout, Caleb Herron, Joseph Chen, Jay Chou, Josiah Lockette
* Assignment Title: Dune Part 2.5
* Assignment Description: This file declares functions in Grid defined
*    in Grid.cpp
* Due Date: 5/2/24
* Date Created: 4/3/24
* Date Last Modified: 5/2/24
*/
#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "SDL_Plotter.h"
class grid {
private:
    int row, col;
    int size;
    color _color;
public:
    /*
     * brief Constructor for the grid class.
     *
     * This constructor initializes a grid object with the
     specified number of rows, columns,
     * size of each cell, and color of the grid lines.
     *
     * parameter r Number of rows in the grid.
     * parameter c Number of columns in the grid.
     * parameter s Size of each cell in the grid.
     * parameter cl Color of the grid lines with RGB values
    */
    grid(int r = 20, int c = 20, int s = 50, color cl = color{});

    /*
    * description: gets the number of rows in the rid
    * return: integer
    * precondition: the grid has a set number of rows
    * postcondition: returns the number of rows in the grid
    */
    int getRow() const;

    /*
    * description: gets the number of columns in the rid
    * return: integer
    * precondition: the grid has a set number of columns
    * postcondition: returns the number of columns in the grid
    */
    int getCol() const;

    /*
    * description: gets the size
    * return: integer
    * precondition: the grid has a set size for each cell
    * postcondition: returns the size of a given cell the grid
    */
    int getSize() const;

    /*
    * description: gets the color of the grid
    * return: color (object included in SDL_Plotter.h)
    * precondition: the grid has a set RGB value
    * postcondition: returns the color object with the grid RGB values
    */
    color getColor() const;

    /*
    * description: sets the number of rows in the grid
    * return: none
    * precondition: some constant integer r exists
    * postcondition: grid has a set number of rows
    */
    void setRow(const int r);

    /*
    * description: sets the number of columns in the grid
    * return: none
    * precondition: some constant integer c exists
    * postcondition: grid has a set number of columns
    */
    void setCol(const int c);

    /*
    * description: sets the size of each cell in the grid
    * return: none
    * precondition: some constant integer s exists
    * postcondition: each cell in the grid has a set size
    */
    void setSize(const int s);

    /*
    * description: sets the color of the grid lines
    * return: none
    * precondition: some constant color object with RGB values exists
    * postcondition: each grid line is set to the RGB value in the color parameter
    */
    void setColor(const color cl);

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
