#pragma once

class Point {
public:
    Point(): x(0), y(0) {}
    Point(int x, int y): x(x), y(y) {}
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    void print() const;

private:
    int x; int y;
};

class Point3D : public Point {
public:
    //Base default constructor called
    //implicitly so x=0 y=0
    Point3D(): z(0) {}

    //Explicitly call base constructor
    Point3D(int x, int y, int z): Point(x,y), z(z) {}

    void setZ(int z) { this->z = z; }
    int getZ() const { return z; }

private:
    int z;
};
