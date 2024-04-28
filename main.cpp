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
    int seasonCount = 0;
    SEASON season = SUMMER;

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
                    if (data[r][c].getType() == RABBIT) {
                        data[r][c].setHealth(17);
                    }
                    else if (data[r][c].getType() == SNAKE) {
                        data[r][c].setHealth(19);
                    }
                    else if (data[r][c].getType() == HAWK) {
                        data[r][c].setHealth(21);
                    }
                    data[r][c].draw(g, season);
                }
		    }
		}

		else if (started) {
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if (data[r][c].getType() >= RABBIT && data[r][c].getType() < SINKHOLE && data[r][c].getHealth() == 0) {
                        data[r][c].setType(EMPTY);
                    }
                }
            }
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if (data[r][c].getType() > RABBIT && data[r][c].getType() < SINKHOLE) {
                        data[r][c].kill(data, r, c);
                    }
                }
            }
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if (data[r][c].getType() >= RABBIT) {
                        data[r][c].reproduce(data, r, c);
                    }
                }
            }
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                        if (data[r][c].getType() >= RABBIT && data[r][c].getType() < SINKHOLE) {
                        //cout << data[r][c].scan(data, r, c) << endl;
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
            for (int r = 0; r < DIM; r++) {
                for (int c = 0; c < DIM; c++) {
                    if(data[r][c].getType() >= RABBIT) {
                        data[r][c].setType(EMPTY);
                        data[r][c].draw(g, season);
                    }
                }
            }
          for (int r = 0; r < DIM; r++) {
            for (int c = 0; c < DIM; c++) {
                if (temp[r][c].getType() >= RABBIT) {
                    data[r][c] = temp[r][c];
                    temp[r][c].setType(EMPTY);
                    data[r][c].updateHealth(-1);
                    cout << data[r][c].getHealth() << endl;
                }
                data[r][c].draw(g, season);
            }
          }
          g.Sleep(300);
          ++seasonCount;
		switch(season) {
		    case SUMMER:
		        if (seasonCount == 15) {
                    season = FALL;
                    seasonCount = 0;
                    for (int r = 0; r < DIM; r++) {
                        for (int c = 0; c < DIM; c++) {
                            if (data[r][c].getType() == CACTUS) {
                                data[r][c].setType(EMPTY);
                            }
                        }
                    }
		        }
            case FALL:
                if (seasonCount == 15) {
                    season = WINTER;
                    seasonCount = 0;
                    for (int r = 0; r < DIM; r++) {
                        for (int c = 0; c < DIM; c++) {
                            if (data[r][c].getType() == OASIS) {
                                data[r][c].setType(EMPTY);
                            }
                        }
                    }
		        }
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
		}
		for (int r = 0; r < DIM; r++) {
            for (int c = 0; c < DIM; c++) {
                if (rand()%1000000 == 0) {
                    if (r < (DIM - 1) && (r > 0) && (c < (DIM - 1)) && (c > 0)) {
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

		_grid.draw(g);
		g.update();
    }
    return 0;
}
