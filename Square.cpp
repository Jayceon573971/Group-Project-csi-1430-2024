#include "Square.h"
square::square() {
    type = EMPTY;
    loc.x = 0;
    loc.y = 0;
    prevLoc = loc;
    _color = color(186, 149, 97);
    size = 20;
    changed = true;
}

void square::setType(TYPE t) {
    type = t;
    changed = true;
}
void square::setColor(color c) {
    _color = c;
    changed = true;
}
void square::setLoc(point p) {
    prevLoc = loc;
    p.x = (p.x / size) * size;
    p.y = (p.y / size) * size;
    loc = p;
    changed = true;
}
void square::setSize(int s) {
    size = s;
}
TYPE square::getType() const {
    return type;
}
color square::getColor() const {
    return _color;
}
point square::getLoc() const {
    return loc;
}

int square::getSize() const {
    return size;
}

void square::draw(SDL_Plotter& g) {
    color _c = _color;
    switch (type) {
        case EMPTY:
            _c = color(186, 149, 97);
            break;
        case OASIS:
            _c = color(0, 255, 255);
            break;
        case CACTUS:
            _c = color(50, 150, 50);
            break;
        case RABBIT:
            _c = color(202, 192, 184);
            break;
        case SNAKE:
            _c = color(0, 0, 0);
            break;
        case HAWK:
            _c = color(255, 87, 51);
            break;
        default:
            _c = color(186, 149, 97);
            break;
    }
    if ((prevLoc.x != loc.x) || (prevLoc.y != loc.y)) {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
            g.plotPixel(c + prevLoc.x, r + prevLoc.y, _c);
            }
        }
        prevLoc = loc;
    }
    if (changed) {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
            g.plotPixel(c + loc.x, r + loc.y, _c);
            }
        }
        changed = false;
    }
}
void allToDefault(square s[][DIM]) {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
                s[r][c].setType(EMPTY);
        }
    }
}
