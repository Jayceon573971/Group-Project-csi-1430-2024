#include "Square (1).h"
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
                if (r % 5 == 0) {
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
    if ((s[cr -1][cc + 1].getType() < curr) && (s[cr -1][cc + 1].getType() > target)) {
        if ((cr - 1) < (DIM - 1) && ((cr - 1) > 0) && ((cc + 1) < (DIM - 1)) && ((cc + 1) > 0)) {
            target = s[cr -1][cc + 1].getType();
            tr = cr -1;
            tc = cc + 1;
            success = true;
        }
    }
    if ((s[cr -1][cc].getType() < curr) && (s[cr -1][cc + 1].getType() > target)) {
        if ((cr - 1) < (DIM - 1) && ((cr - 1) > 0)) {
            target = s[cr -1][cc].getType();
            tr = cr -1;
            tc = cc;
            success = true;
        }
    }
    if ((s[cr -1][cc - 1].getType() < curr) && (s[cr -1][cc + 1].getType() > target)) {
        if ((cr - 1) < (DIM - 1) && ((cr - 1) > 0) && ((cc - 1) < (DIM - 1)) && ((cc - 1) > 0)) {
            target = s[cr -1][cc + 1].getType();
            tr = cr -1;
            tc = cc - 1;
            success = true;
        }
    }
    if (s[cr][cc - 1].getType() < curr && s[cr -1][cc - 1].getType() > target) {
        if (((cc - 1) < (DIM - 1)) && ((cc - 1) > 0)) {
            target = s[cr][cc - 1].getType();
            tr = cr;
            tc = cc - 1;
            success = true;
        }
    }
    if (s[cr + 1][cc - 1].getType() < curr && s[cr -1][cc - 1].getType() > target) {
        if ((cr + 1) < (DIM - 1) && ((cr + 1) > 0) && ((cc - 1) < (DIM - 1)) && ((cc - 1) > 0)) {
            target = s[cr -1][cc - 1].getType();
            tr = cr + 1;
            tc = cc - 1;
            success = true;
        }
    }
    if ((s[cr + 1][cc].getType() < curr) && (s[cr + 1][cc].getType() > target)) {
        if ((cr + 1) < (DIM - 1) && ((cr + 1) > 0) && ((cc) < (DIM - 1)) && ((cc) > 0)) {
            target = s[cr + 1][cc].getType();
            tr = cr -1;
            tc = cc;
            success = true;
        }
    }
    if ((s[cr + 1][cc + 1].getType() < curr) && (s[cr -1][cc + 1].getType() > target)) {
        if ((cr + 1) < (DIM - 1) && ((cr + 1) > 0) && ((cc + 1) < (DIM - 1)) && ((cc + 1) > 0)) {
            target = s[cr -1][cc + 1].getType();
            tr = cr + 1;
            tc = cc + 1;
            success = true;
        }
    }
    if ((s[cr][cc + 1].getType() < curr) && (s[cr -1][cc + 1].getType() > target)) {
        if ((cr) < (DIM - 1) && ((cr) > 0) && ((cc + 1) < (DIM - 1)) && ((cc + 1) > 0)) {
            target = s[cr -1][cc + 1].getType();
            tr = cr;
            tc = cc + 1;
            success = true;
        }
    }
    //cout << target << endl;

        if (success) {
            s[tr][tc].setType(EMPTY);
            if (target < RABBIT) {
                s[cr][cc].updateHealth(2);
            }
            else if (target == RABBIT) {
                s[cr][cc].updateHealth(5);
            }
            else if (target == SNAKE) {
                s[cr][cc].updateHealth(7);
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
    if (curr > OASIS) {
        bool found = false;
        if ((cr - 1) < (DIM - 1) && ((cr - 1) > 0) && ((cc + 1) < (DIM - 1)) && ((cc + 1) > 0)) {
            if (s[cr -1][cc + 1].getType() == curr) {
                found = true;
            }
            else if (s[cr - 1][cc + 1].getType() == EMPTY) {
                emptyR = cr - 1;
                emptyC = cc + 1;
            }
        }
    if ((cr - 1) < (DIM - 1) && ((cr - 1) > 0)) {
            if (s[cr -1][cc].getType() == curr) {
                found = true;
            }
            else if (s[cr - 1][cc].getType() == EMPTY) {
                emptyR = cr - 1;
                emptyC = cc;
            }
        }
    if ((cr - 1) < (DIM - 1) && ((cr - 1) > 0) && ((cc - 1) < (DIM - 1)) && ((cc - 1) > 0)) {
            if (s[cr -1][cc - 1].getType() == curr) {
                found = true;
            }
            else if (s[cr - 1][cc - 1].getType() == EMPTY) {
                emptyR = cr - 1;
                emptyC = cc - 1;
            }
        }
    if (((cc - 1) < (DIM - 1)) && ((cc - 1) > 0)) {
            if (s[cr][cc - 1].getType() == curr) {
                found = true;
            }
            else if (s[cr][cc - 1].getType() == EMPTY) {
                emptyR = cr;
                emptyC = cc - 1;
            }
        }
    if ((cr + 1) < (DIM - 1) && ((cr + 1) > 0) && ((cc - 1) < (DIM - 1)) && ((cc - 1) > 0)) {
            if (s[cr + 1][cc - 1].getType() == curr) {
                found = true;
            }
            else if (s[cr + 1][cc - 1].getType() == EMPTY) {
                emptyR = cr + 1;
                emptyC = cc - 1;
            }
        }
    if ((cr + 1) < (DIM - 1) && ((cr + 1) > 0)) {
            if (s[cr + 1][cc].getType() == curr) {
                found = true;
            }
            else if (s[cr + 1][cc].getType() == EMPTY) {
                emptyR = cr + 1;
                emptyC = cc;
            }
        }
    if ((cr + 1) < (DIM - 1) && ((cr + 1) > 0) && ((cc + 1) < (DIM - 1)) && ((cc + 1) > 0)) {
            if (s[cr + 1][cc + 1].getType() == curr) {
                found = true;
            }
            else if (s[cr + 1][cc + 1].getType() == EMPTY) {
                emptyR = cr + 1;
                emptyC = cc + 1;
            }
        }
    if (((cc + 1) < (DIM - 1)) && ((cc + 1) > 0)) {
            if (s[cr][cc + 1].getType() == curr) {
                found = true;
            }
            else if (s[cr][cc + 1].getType() == EMPTY) {
                emptyR = cr;
                emptyC = cc + 1;
            }
        }
    if (found) {
        if (curr == RABBIT) {
            if (rand() % 6 == 0) {
                s[emptyR][emptyC].setType(curr);
                s[emptyR][emptyC].setHealth(10);
            }
        }
        else if (curr == SNAKE) {
            if (rand() % 12 == 0) {
                s[emptyR][emptyC].setType(curr);
                s[emptyR][emptyC].setHealth(10);
            }
        }
        else if (curr == HAWK) {
            if (rand() % 18 == 0) {
                s[emptyR][emptyC].setType(curr);
                s[emptyR][emptyC].setHealth(10);
            }
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
