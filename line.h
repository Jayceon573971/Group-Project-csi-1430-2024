/*
* Authors: Collin Strout, Caleb Herron, Joseph Chen, Jay Chou, Josiah Lockette
* Assignment Title: Dune Part 2.5
* Assignment Description: This file declares functions in Line defined
*    in Line.cpp
* Due Date: 5/2/24
* Date Created: 4/3/24
* Date Last Modified: 5/2/24
*/

#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include "SDL_Plotter.h"

/*
* description: plots pixels in a line
* return: none
* precondition: valid int for x and y points as well as
*               RGB and g (SDL Plotter) are given
* postcondition: line is drawn
*/
void drawLine(int x1, int y1, int x2, int y2, int R, int G, int B, SDL_Plotter& g);

/*
* description: returns slope from two given points
* return: double
* precondition: valid int for x and y are given
* postcondition: slope is returned
*/
double slope(int x1, int y1, int x2, int y2);

/*
* description: returns y intercept from two points
* return: double
* precondition: valid int for x and y are given
* postcondition: y Intercept is returned
*/
double y_intercept(int x1, int y1, int x2, int y2);

/*
* description: returns true or false if two points
            have valid slope
* return: boolean
* precondition: valid int for x and y are given
* postcondition: true or false is returned
*/
bool hasSlope(int x1, int y1, int x2, int y2);
#endif // LINE_H_INCLUDED
