#include "Square.h"
square::square() {
    type = EMPTY;
    _color = color(186, 149, 97);
    health = 0;
}

void square::setType(TYPE t) {
    type = t;
}
void square::setColor(color c) {
    _color = c;
}

void square::setCol(int col) {
    this -> col = col;
}

void square::setRow(int row) {
    this -> row = row;
}
void square::setHealth(int h) {
    health = h;
}
void square::updateHealth(int h) {
    health += h;
    if (health < 0) {
        health = 0;
    }
}

TYPE square::getType() const {
    return type;
}
color square::getColor() const {
    return _color;
}

int square::getCol() const {
    return col;
}

int square::getRow() const {
    return row;
}

int square::getHealth() const {
    return health;
}


void square::draw(SDL_Plotter& g, SEASON& season) {
    switch (type) {
        case EMPTY:
            if (season == SUMMER) {
                setColor(color(186, 149, 97));
            }
            else if (season == FALL) {
                setColor(color(166, 129, 77));
            }
            else if (season == WINTER) {
                setColor(color(225, 222, 216));
            }
            else if (season == SPRING) {
                setColor(color(118, 100, 61));
            }
            break;
        case OASIS:
            setColor(color(0, 255, 255));
            break;
        case CACTUS:
            setColor(color(50, 150, 50));
            break;
        case RABBIT:
            setColor(color(202, 192, 184));
            break;
        case SNAKE:
            setColor(color(0, 0, 0));
            break;
        case HAWK:
            setColor(color(255, 87, 51));
            break;
        case SINKHOLE:
            setColor(color(15, 11, 13));
            break;
        default:
            setColor(color(186, 149, 97));
            break;
    }

    for (int r = 0; r < SIDE; r++) {
        for (int c = 0; c < SIDE; c++) {
            g.plotPixel(c + SIDE * col, r + SIDE * row, getColor());
        }
    }
}

char square::scan(square s[][DIM], int cr, int cc) {
    TYPE curr = s[cr][cc].getType();
    TYPE targetRow = EMPTY;
    TYPE targetCol = EMPTY;
    int tr;
    int tc;
    char dir;

    for (int r = 0; r < DIM; r++) {
        if (r != cr) {
            TYPE other = s[r][cc].getType();
            if (other == curr) {
                if (rand() % 3 == 0) {
                    targetRow = other;
                    tr = r;
                }
            }
            else if ((other > targetRow) && (other < curr)) {
                targetRow = other;
                tr = r;
            }
        }
    }

    for (int c = 0; c < DIM; c++) {
        if (c != cc) {
            TYPE other = s[cr][c].getType();
            if (other == curr) {
                if (rand() % 3 == 0) {
                    targetCol = other;
                    tc  = c;
                }
            }
            else if ((other > targetCol) && (other < curr)) {
                targetCol = other;
                tc = c;
            }
        }
    }

    // Move to New Row and Column if nothing is sensed
    if ((targetRow == EMPTY) && (targetCol == EMPTY)) {
            dir = 'z';
    }
    else if (targetRow > targetCol) {
        if (tr > cr) {
            dir = 'd';
        }
        else {
            dir = 'u';
        }
    }
    else if (targetRow < targetCol) {
        if (tc > cc) {
            dir = 'r';
        }
        else {
            dir = 'l';
        }
    }
    else { // Same Type and Not EMPTY
        if(abs(tc - cc) < abs(tr - cr)) {
            if (tc > cc) {
                dir = 'r';
            }
            else {
                dir = 'l';
            }
        }
        else if (abs(tc - cc) > abs(tr - cr)) {
            if (tr > cr) {
                dir = 'd';
            }
            else {
                dir = 'u';
            }
        }
        else { // equal distance and same type
            if (rand() % 2 == 0) {
                if (tc > cc) {
                    dir = 'r';
                }
                else {
                    dir = 'l';
                }
            }
            else {
                if (tr > cr) {
                    dir = 'l';
                }
                else {
                    dir = 'l';
                }
            }
        }
    }
    return dir;
}

int square::moveINX(square s[][DIM], int cr, int cc) {
    int newCol = cc;
    char dir = s[cr][cc].scan(s, cr, cc);

    switch (dir) {
        case 'r':
            newCol += 1;
            break;
        case 'l':
            newCol -=1;
        case 'z':
            if (rand() % 2 == 0) {
                newCol += 1;
            }
            else {
                newCol -= 1;
            }
            break;
    }

    if ((newCol > (DIM - 1)) || (newCol < 0)) {
        newCol = cc;
    }
    if (s[cr][newCol].getType() != EMPTY) {
        newCol = cc;
    }
    return newCol;
}

int square::moveINY(square s[][DIM], int cr, int cc) {
    int newRow = cr;
    char dir = s[cr][cc].scan(s, cr, cc);

    switch (dir) {
        case 'd':
            newRow += 1;
            break;
        case 'u':
            newRow -= 1;
            break;
        case 'z':
            if (rand() % 2 == 0) {
                newRow += 1;
            }
            else {
                newRow -= 1;
            }
            break;
    }

    if ((newRow > (DIM - 1)) || (newRow < 0)) {
        newRow = cr;
    }
    if (s[newRow][cc].getType() != EMPTY) {
        newRow = cr;
    }
    return newRow;
}

void square::move(int r, int c) {
    setRow(r);
    setCol(c);
    switch (type) {
        case EMPTY:
            setColor(color(186, 149, 97));
            break;
        case OASIS:
            setColor(color(0, 255, 255));
            break;
        case CACTUS:
            setColor(color(50, 150, 50));
            break;
        case RABBIT:
            setColor(color(202, 192, 184));
            break;
        case SNAKE:
            setColor(color(0, 0, 0));
            break;
        case HAWK:
            setColor(color(255, 87, 51));
            break;
        default:
            setColor(color(186, 149, 97));
            break;
    }
}

void square::kill(square s[][DIM], int cr, int cc) {
    TYPE curr = s[cr][cc].getType();
    if (curr >= RABBIT) {
    TYPE target = EMPTY;
    int tr = cr;
    int tc = cc;
    bool success = false;
    for (int r = cr - 1; r < cr + 2; r++) {
        for (int c = cc - 1; c < cc + 2; c++) {
            if (r != cr && c != cc) {
                if (r < DIM && r > 0 && c < DIM && c > 0) {
                    TYPE other = s[r][c].getType();
                    if (other < curr && other > target) {
                        target = other;
                        tr = r;
                        tc = c;
                        success = true;
                    }
                }
            }
        }
    }

        if (success) {
            s[tr][tc].setType(EMPTY);
            switch (target) {
                case OASIS:
                    s[cr][cc].updateHealth(2);
                    break;
                case CACTUS:
                    s[cr][cc].updateHealth(2);
                    break;
                case RABBIT:
                    s[cr][cc].updateHealth(5);
                    break;
                case SNAKE:
                    s[cr][cc].updateHealth(7);
                    break;
            }
        }
    }
}
void square::reset() {
    setHealth(0);
    setType(EMPTY);
}
void square::reproduce(square s [][DIM], int cr, int cc) {
    TYPE curr = s[cr][cc].getType();
    int emptyR = cr;
    int emptyC = cc;
    if (curr > CACTUS) {
        bool found = false;
        for (int r = cr - 1; r < cr + 2; r++) {
            for (int c = cc - 1; c < cc + 2; c++) {
                if (r != cr && c != cc) {
                    if (r < DIM && r > 0 && c < DIM && c > 0) {
                        TYPE other = s[r][c].getType();
                        if (other == curr) {
                            found = true;
                        }
                        else if (other == EMPTY) {
                            emptyR = r;
                            emptyC = c;
                        }
                    }
                }
            }
        }

        if (found) {
            switch (curr) {
                case RABBIT:
                    if (rand() % 6 == 0) {
                        s[emptyR][emptyC].setType(curr);
                        s[emptyR][emptyC].setHealth(15);
                    }
                    break;
                case SNAKE:
                    if (rand() % 12 == 0) {
                        s[emptyR][emptyC].setType(curr);
                        s[emptyR][emptyC].setHealth(10);
                    }
                    break;
                case HAWK:
                    if (rand() % 18 == 0) {
                        s[emptyR][emptyC].setType(curr);
                        s[emptyR][emptyC].setHealth(10);
                    }
                    break;
                case SINKHOLE:
                    if (rand() % 5000 == 0) {
                        s[emptyR][emptyC].setType(curr);
                    }
                    break;
            }
        }
    }
}

void allToDefault(square s[][DIM]) {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            s[r][c].setType(EMPTY);
            s[r][c].setColor(color(186, 149, 97));
        }
    }
}
