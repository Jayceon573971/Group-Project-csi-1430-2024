/*
* Authors: Colin Strout, Caleb Herron, Joseph Chen, Jay Chou, Josiah Lockette
* Assignment Title: Dune Part 2.5
* Assignment Description: This is a ecosystem simulation game that simulates
* an ecosystem in the desert
* Due Date: 5/2/2024
* Date Created: 4/3/2024
* Date Last Modified: 5/2/2024
*/

#include <iostream>
#include <cmath>
#include <ctime>
#include "SDL_Plotter.h"
#include "Grid.h"
#include "Square.h"
using namespace std;

int main(int argc, char ** argv) {
    // Data Abstraction: declare variables for simulation
    TYPE type;
    TYPE curr;
    SDL_Plotter g(SIZE,SIZE);
    grid _grid(SIZE, SIZE, SIDE, color(0,0,0));
    bool started = false;
    square data[DIM][DIM];
    square temp[DIM][DIM];
    int newR;
    int newC;
    int seasonCount = 0;
    SEASON season = SUMMER;
    int seedValue = time(0);
    seedValue -= seedValue % 300;
    srand(seedValue);

    //Initializes Data, all squares in the data have a given
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            data[r][c].setCol(c);
            data[r][c].setRow(r);
        }
    }

    // Input: Get's User Key Input
    while (!g.getQuit()) {
        if(g.kbhit()){
            switch(toupper(g.getKey())) {
                case 'E':
                    type = EMPTY;
                    break;
                case 'C':
                    type = CACTUS;
                    break;
                case 'O':
                    type = OASIS;
                    break;
                case 'R':
                    type = RABBIT;
                    break;
                case 'S':
                    type = SNAKE;
                    break;
                case 'H':
                    type = HAWK;
                    break;
                case 'D':
                    if (!started) {
                        allToDefault(data);
                        type = EMPTY;
                    }
                    break;
                case 'P':
                    started = true;
                    break;
                default:
                    type = EMPTY;
                    break;
		    }
		}

		if(!started){
		    if (g.mouseClick()) {
                // Sets type of square where cursor is clicked
                // to the type selected
                point p = (g.getMouseClick());
		        data[p.y/SIDE][p.x/SIDE].setType(type);
		    }

		    for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if (data[r][c].getType() == RABBIT) {
                        data[r][c].setHealth(30);
                    }
                    else if (data[r][c].getType() == SNAKE) {
                        data[r][c].setHealth(40);
                    }
                    else if (data[r][c].getType() == HAWK) {
                        data[r][c].setHealth(50);
                    }
                    data[r][c].draw(g, season);
                }
		    }
		}

		// Process
		else if (started) {
            // Check's if a given organism dies from hunger, is killed from an
            // organism, or if it reproduces
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    data[r][c].die();
                }
            }

            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    data[r][c].kill(data, r, c);
                }
            }

            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    data[r][c].reproduce(data, r, c);
                }
            }

            // Copies every type into temporary 2D array unless
            // the square is empty, including simulated movement
            // for organisms that can move
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    curr = data[r][c].getType();
                        if (curr >= RABBIT && curr < SINKHOLE) {
                            newR = data[r][c].moveINY(data, r, c);
                            newC = data[r][c].moveINX(data, r, c);
                            temp[newR][newC] = data[r][c];
                            temp[newR][newC].move(newR, newC);
                        }
                        else if (data[r][c].getType() > EMPTY) {
                            temp[r][c] = data[r][c];
                            temp[r][c].move(r,c);
                        }
                }
            }

            // Makes the type of every organism in the original
            // grid empty, as this was their previous location
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    curr = data[r][c].getType();
                    if(curr >= RABBIT) {
                        data[r][c].reset();
                        data[r][c].draw(g, season);
                    }
                }
            }
            // Copies the new location of every organism
            // into the original 2D array and decrements
            // their health by 1
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if (temp[r][c].getType() >= RABBIT) {
                        data[r][c] = temp[r][c];
                        temp[r][c].setType(EMPTY);
                        data[r][c].updateHealth(-1);
                    }
                    data[r][c].draw(g, season);
                }
            }
            g.Sleep(300);
            seasonCount++;
		    // Changes season based on season count
		    // which changes every 15 loops
		    switch(season) {
                case SUMMER:
		            if (seasonCount == 15) {
                        season = FALL;
                        seasonCount = 0;
                        for (int r = 0; r < DIM; r++) {
                            for (int c = 0; c < DIM; c++) {
                                if (data[r][c].getType() == CACTUS) {
                                    data[r][c].reset();
                                }
                            }
                        }
		            }
		            break;
                case FALL:
                    if (seasonCount == 15) {
                        season = WINTER;
                        seasonCount = 0;
                        for (int r = 0; r < DIM; r++) {
                            for (int c = 0; c < DIM; c++) {
                                if (data[r][c].getType() == OASIS) {
                                    data[r][c].reset();
                                }
                            }
                        }
		            }
		            break;
                case WINTER:
                    if (seasonCount == 15) {
                        season = SPRING;
                        seasonCount = 0;
                        for (int r = 0; r < DIM; r++) {
                            for (int c = 0; c < DIM; c++) {
                                if (data[r][c].getType() == EMPTY) {
                                    if(rand()%50 == 0)
                                        data[r][c].setType(OASIS);
                                }
                            }
                        }
		            }
		            break;
                case SPRING:
                    if (seasonCount == 15) {
                        season = SUMMER;
                        seasonCount = 0;
                        for (int r = 0; r < DIM; r++) {
                            for (int c = 0; c < DIM; c++) {
                                if (data[r][c].getType() == EMPTY) {
                                    if(rand()%50 == 0)
                                        data[r][c].setType(CACTUS);
                                }
                            }
                        }
		            }
		            break;
            }

            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if (rand() % 1000000 == 0) {
                        if (r < (DIM - 1) && (r > 0)) {
                            if ((c < (DIM - 1)) && (c > 0)) {
                                data[r-1][c].setType(SINKHOLE);
                                data[r-1][c+1].setType(SINKHOLE);
                                data[r][c+1].setType(SINKHOLE);
                                data[r][c].setType(SINKHOLE);
                                cout << "ND" << endl;
                            }
                        }
                    }
                }
            }
		}
		// Output: Displays updated 2-D array to the plotter screen
		_grid.draw(g);
		g.update();
    }
    return 0;
}
