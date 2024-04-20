#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"
#include "Grid.h"
#include "Square.h"
using namespace std;

const int SIZE = 1000;
const int SIDE = 20;
const int DIM = SIZE / SIDE;

void allToDefault(square s[][DIM]) {
    int dim = SIZE / SIDE;
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
                s[r][c].setType(EMPTY);
        }
    }
}

int main(int argc, char ** argv) {

    TYPE type;
    SDL_Plotter g(SIZE,SIZE);
    grid _grid(SIZE, SIZE, SIDE, color(0,0,0));
    square sq1;
    square data[DIM][DIM];

    //Init Data
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            data[r][c].setLoc(point(c * SIDE, r * SIDE));
        }
    }

    while (!g.getQuit()) {
		if(g.kbhit()){
            switch(toupper(g.getKey())) {
                case 'E': type = EMPTY;
		                  break;
                case 'C': type = CACTUS;
                          break;
                case 'O': type = OASIS;
                          break;
                case 'R': type = RABBIT;
                          break;
                case 'S': type = SNAKE;
                          break;
                case 'H': type = HAWK;
                          break;
                case 'D': allToDefault(data);
                          break;
		    }
		}

		if(g.mouseClick()){
		    point p = (g.getMouseClick());
		    data[p.y/SIDE][p.x/SIDE].setType(type);
		}

		for (int r = 0; r < DIM; r++) {
            for (int c = 0; c < DIM; c++) {
                data[r][c].draw(g);
            }
		}
		_grid.draw(g);
		g.update();

    }
    return 0;
}
