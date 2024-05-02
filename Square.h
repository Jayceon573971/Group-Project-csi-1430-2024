/*
* Authors: Collin Strout, Caleb Herron, Joseph Chen, Jay Chou, Josiah Lockette
* Assignment Title: Dune Part 2.5
* Assignment Description: This file declares functions in square defined
*    in square.cpp
* Due Date: 5/2/24
* Date Created: 4/3/24
* Date Last Modified: 5/2/24
*/

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

    /*
     * description: Sets the type of each individual square
     * return: void
     * precondition: ENUM TYPE declared
     * postcondition: sets the type of a square
     *
    */
    void setType(TYPE);
    /*
     * description: Sets the color of each individual square
     * return: void
     * precondition: color declared
     * postcondition: sets the color of a square
     *
    */
    void setColor(color);
    /*
     * description: Sets the row each square appears on
     * return: void
     * precondition:
     * postcondition: sets the row of a square
     *
    */
    void setRow(int);
    /*
     * description: Sets the collumn each square appears on
     * return: void
     * precondition:
     * postcondition: sets the column of a square
     *
    */
    void setCol(int);
    /*
     * description: Sets the health of each character
     * return: void
     * precondition:
     * postcondition: sets the health of a square
     *
    */
    void setHealth(int);
    /*
     * description: Adds one hp to a square
     * return: void
     * precondition:
     * postcondition: Adds one to health
     *
    */
    void updateHealth(int);

    /*
     * description: Returns the type of a square
     * return: TYPE
     * precondition: Type is set
     * postcondition: Gets the type of a square
     *
    */
    TYPE getType() const;
    /*
     * description: Gets the color each square appears on
     * return: color
     * precondition: Color is set
     * postcondition: gets the health of a square
     *
    */
    color getColor() const;
    /*
     * description: Gets the row each square appears on
     * return: int
     * precondition: Row is set
     * postcondition: Gets the row of a square
     *
    */
    int getRow() const;
    /*
     * description: Gets the column each square appears on
     * return: int
     * precondition: Column is set
     * postcondition: Gets the column of a square
     *
    */
    int getCol() const;
    /*
     * description: Gets the health each square appears on
     * return: int
     * precondition: Health is set
     * postcondition: Gets the health of a square
     *
    */
    int getHealth() const;

    /*
     * description: Draws the color of each square in the grid
     * return: void
     * precondition:
     * postcondition: Draws the colors for each square
     *
    */
    void draw(SDL_Plotter& g, SEASON&);
    /*
     * description: Selects a square and scans squares in the rows and columns
     * return: char
     * precondition: SEASON enum set
     * postcondition: Returns an char based on the type of squares in row and
     *                columns
     *
    */
    char scan(square[][DIM], int, int);
    /*
     * description: Moves the square in the x direction if scan returns a
     *              cactus or oasis
     * return: int
     * precondition: scan was run
     * postcondition: Moves a square in x direction
     *
    */
    int moveINX(square[][DIM], int, int);
    /*
     * description: Moves the square in the y direction if scan returns a
     *              cactus or oasis
     * return: int
     * precondition: scan was run
     * postcondition: Moves a square in y direction
     *
    */
    int moveINY(square[][DIM], int, int);
    /*
     * description: Swaps the current square type with the empty type it
     *              moves to
     * return: int
     * precondition: scan was run
     * postcondition: Swaps the position of two squares
     *
    */
    void move(int, int);
    void kill(square[][DIM], int, int);
    void reproduce(square[][DIM], int, int);
    void reset();
    void die();
};

void allToDefault(square s[][DIM]);

#endif // SQUARE_H_INCLUDED
