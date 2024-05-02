/*
 * brief Constructor for the grid class.
 *
 * This constructor initializes a grid object with the specified number of rows, columns,
 * size of each cell, and color of the grid lines.
 *
 * param r Number of rows in the grid.
 * param c Number of columns in the grid.
 * param s Size of each cell in the grid.
 * param cl Color of the grid lines.
 */
grid::grid(int r, int c, int s, color cl) {
    row = r;
    col = c;
    size = s;
    _color = cl;
}

/*
 * brief Get the number of rows in the grid.
 *
 * return The number of rows in the grid.
 */
int grid::getRow() const {
    return row;
}

/*
 * brief Get the number of columns in the grid.
 *
 * return The number of columns in the grid.
 */
int grid::getCol() const {
    return col;
}

/*
 * brief Get the size of each cell in the grid.
 *
 * return The size of each cell in the grid.
 */
int grid::getSize() const {
    return size;
}

/*
 * brief Get the color of the grid lines.
 *
 * return The color of the grid lines.
 */
color grid::getColor() const {
    return _color;
}

/*
 * brief Set the number of rows in the grid.
 *
 * param r The number of rows to set.
 */
void grid::setRow(const int r) {
    row = r;
}

/*
 * brief Set the number of columns in the grid.
 *
 * param c The number of columns to set.
 */
void grid::setCol(const int c) {
    col = c;
}

/*
 * brief Set the size of each cell in the grid.
 *
 * param s The size of each cell to set.
 */
void grid::setSize(const int s) {
    size = s;
}

/*
 * brief Set the color of the grid lines.
 *
 * param cl The color of the grid lines to set.
 */
void grid::setColor(const color cl) {
    _color = cl;
}

/*
 * brief Draw the grid on the specified SDL plotter.
 *
 * This function draws the grid lines on the specified SDL plotter object.
 *
 * param g Reference to the SDL plotter object.
 */
void grid::draw(SDL_Plotter& g) {
    int maxRow = g.getRow();
    int maxCol = g.getCol();

    for (int c = 0; c < col; c++) {
        drawLine(c * size, 0, c * size, maxRow - 1, _color.R, _color.G, _color.B, g);
    }
    for (int r = 0; r < row; r++) {
        drawLine(0, r * size, maxCol - 1, r * size, _color.R, _color.G, _color.B, g);
    }
}
