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
    square temp[DIM][DIM];
    int newR;
    int newC;

    //Init Data
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            data[r][c].setCol(c);
            data[r][c].setRow(r);
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

		if(!started){
		    if (g.mouseClick()) {
		        point p = (g.getMouseClick());
		        data[p.y/SIDE][p.x/SIDE].setType(type);
		    }
		    for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    data[r][c].draw(g);
                }
		    }
		}

		else if (started) {
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                        if (data[r][c].getType() >= RABBIT) {
                        cout << data[r][c].scan(data, r, c) << endl;
                        newR = data[r][c].moveINY(data, r, c);
                        newC = data[r][c].moveINX(data, r, c);

                        temp[newR][newC] = data[r][c];
                        temp[newR][newC].move(newR, newC);
                        }
                }
            }
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if(data[r][c].getType() >= RABBIT) {
                        data[r][c].setType(EMPTY);
                        data[r][c].draw(g);
                    }
                }
            }

          for (int r = 0; r < DIM; r++) {
            for (int c = 0; c < DIM; c++) {
                if (temp[r][c].getType() >= RABBIT) {
                    data[r][c] = temp[r][c];
                    temp[r][c].setType(EMPTY);
                }
                data[r][c].draw(g);
            }
          }
          g.Sleep(300);
		}

		_grid.draw(g);
		g.update();

    }
    return 0;
}
