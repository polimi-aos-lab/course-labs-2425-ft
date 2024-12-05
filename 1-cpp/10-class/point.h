#pragma once

class Point {
public:
    Point(): x(0), y(0) {}
    Point(int x, int y): x(x), y(y) {}
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    void print();

private:
    int x; int y;
};
