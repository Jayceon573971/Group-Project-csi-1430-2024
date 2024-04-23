#include <iostream>
#include <cmath>
#include <ctime>
#include "SDL_Plotter.h"
#include "Grid.h"
#include "Square.h"
using namespace std;

int main(int argc, char ** argv) {

    TYPE type;
    SDL_Plotter g(SIZE,SIZE);
    grid _grid(SIZE, SIZE, SIDE, color(0,0,0));
    bool started = false;
    square data[DIM][DIM];
    int time = clock();

    //Init Data
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            data[r][c].setLoc(point(c * SIDE, r * SIDE));
        }
    }

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

		if(g.mouseClick() && !started){
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
