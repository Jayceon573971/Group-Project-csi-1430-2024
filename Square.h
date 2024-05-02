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

    /*
     * description: Default constructor
     * return: void
     * precondition: Square object declared
     * postcondition: sets the type of a square to empty,
     * health to 0, and color to base summer sand color
     *
    */
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
     * precondition: A plotter is declared and there is a season
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
     * return: none
     * precondition: scan was run
     * postcondition: Swaps the position of two squares
     *
    */
    void move(int, int);


    /*
     * description: Searches the squares within one tile of it's current
     *              location and makes the square of the highest type that
     *              is less than it empty
     * return: none
     * precondition: Square's type must be at least a rabbit
     * postcondition: Makes the type of the selected square empty and give
     *                the current square extra health
     *
    */
    void kill(square[][DIM], int, int);

    /*
     * description: Searches the squares within one tile of it's current
     *              location and makes an empty square the same type as itself
     * return: none
     * precondition: Square's type must be at least a rabbit
     * postcondition: Makes the type of the selected square that is empty its
     * type and sets it's health to a given health based on its new type
     *
    */
    void reproduce(square[][DIM], int, int);


    /*
     * description: Sets the type of a square to empty and health to 0,
     * this function is meant to be used in the swap phase from the temporary
     * 2D array in main.cpp
     * return: none
     * precondition: The square has a type
     * postcondition: Makes the type of the square empty and health to 0
     *
    */
    void reset();

    /*
     * description: Sets the type of a square to empty and health to 0,
     * uses the reset function (simulates dying from hunger)
     * return: none
     * precondition: The square's type is at least Rabbit and can't be greater
     * than a Hawk
     * postcondition: Makes the type of the square empty and health to 0
     *
    */
    void die();
};

/*
* description: Sets the type of a square to empty and color to the
* summer sand color
* return: none
* precondition: The simulation has not started yet (P key is not pressed)
* postcondition: Makes the type of every square empty
*
*/
void allToDefault(square s[][DIM]);

#endif // SQUARE_H_INCLUDED
