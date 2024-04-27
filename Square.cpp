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
    h = health;
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


void square::draw(SDL_Plotter& g) {
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

    for (int r = 0; r < SIDE; r++) {
        for (int c = 0; c < SIDE; c++) {
            g.plotPixel(c + SIDE * col, r + SIDE * row, getColor());
        }
    }
}

string square::scan(square s[][DIM], int cr, int cc) {
    TYPE currType = s[cr][cc].getType();
    TYPE targetRow = EMPTY;
    TYPE targetCol = EMPTY;
    int tr;
    int tc;
    string dir;

    for (int r = 0; r < DIM; r++) {
        if (r != cr) {
            TYPE other = s[r][cc].getType();
            if (other == currType) {
                int r = rand();
                if (r % 2 == 0) {
                    targetRow = other;
                    tr = r;
                }
            }
            else if ((other > targetRow) && (other < currType)) {
                targetRow = other;
                tr = r;
            }
        }
    }

    for (int c = 0; c < DIM; c++) {
        if (c != cc) {
            TYPE other = s[cr][c].getType();
            if (other == currType) {
                int r = rand();
                if (r % 2 == 0) {
                    targetCol = other;
                    tc  = c;
                }
            }
            else if ((other > targetCol) && (other < currType)) {
                targetCol = other;
                tc = c;
            }
        }
    }

    // Move to New Row and Column if nothing is sensed
    if ((targetRow == EMPTY) && (targetCol == EMPTY)) {
            dir = "diagonal";
    }
    else if (targetRow > targetCol) {
        if (tr > cr) {
            dir = "down";
        }
        else {
            dir = "up";
        }
    }
    else if (targetRow < targetCol) {
        if (tc > cc) {
            dir = "right";
        }
        else {
            dir = "left";
        }
    }
    else { // Same Type and Not EMPTY
        if(abs(tc - cc) < abs(tr - cr)) {
            if (tc > cc) {
                dir = "right";
            }
            else {
                dir = "left";
            }
        }
        else if (abs(tc - cc) > abs(tr - cr)) {
            if (tr > cr) {
                dir = "down";
            }
            else {
                dir = "up";
            }
        }
        else { // equal distance and same type
            int r = rand();
            if (r % 2 == 0) {
                if (tc > cc) {
                    dir = "right";
                }
                else {
                    dir = "left";
                }
            }
            else {
                if (tr > cr) {
                    dir = "down";
                }
                else {
                    dir = "up";
                }
            }
        }
    }
    return dir;
}

int square::moveINX(square s[][DIM], int cr, int cc) {
    int newCol = cc;
    string dir = s[cr][cc].scan(s, cr, cc);

    if (dir == "left") {
        newCol -= 1;
    }
    else if (dir == "right") {
        newCol += 1;
    }
    else if (dir == "diagonal") {
        int r = rand();
        if (r % 2 == 0) {
            newCol += 1;
        }
        else {
            newCol -= 1;
        }
        if ((s[cr + 1][newCol].getType() != EMPTY)) {
            newCol = cc;
        }
        if ((s[cr - 1][newCol].getType() != EMPTY)) {
            newCol = cc;
        }
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
    string dir = s[cr][cc].scan(s, cr, cc);

    if (dir == "up") {
        newRow -= 1;
    }
    else if (dir == "down") {
        newRow += 1;
    }
    else if (dir == "diagonal") {
        int r = rand();
        if (r % 2 == 0) {
            newRow += 1;
        }
        else {
            newRow -= 1;
        }
        if ((s[newRow][cc - 1].getType() != EMPTY)) {
            newRow = cr;
        }
        if ((s[newRow][cc + 1].getType() != EMPTY)) {
            newRow = cr;
        }
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
    TYPE target = EMPTY;
    int tr = cr;
    int tc = cc;
    if (curr >= RABBIT) {
        for (int r = cr - 1; r < cr + 2; r++) {
            for (int c = cc - 1; c < cc + 2; c++) {
                if (r != cr && c != cc) {
                    TYPE other = s[r][c].getType();
                    if ((other < curr) && (other > target)) {
                        if (r < (DIM - 1) && (r > 0) && (c < (DIM - 1)) && (c > 0)) {
                            target = other;
                            tr = r;
                            tc = c;
                        }
                    }
                }
            }
        }
    }

    if (tr != cr && tc != cc) {
        s[tr][tc].setType(EMPTY);
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
