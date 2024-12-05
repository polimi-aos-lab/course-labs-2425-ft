#pragma once

class Point {
public:
    virtual void print() const = 0; //Pure virtual
};

class Point2D : public Point {
public:
    Point2D(): x(0), y(0) {}
    Point2D(int x, int y): x(x), y(y) {}
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    virtual void print() const;
protected:
    int x; int y;
};

class Point3D : public Point2D {
public:
    Point3D(): z(0) {}
    Point3D(int x, int y, int z)
	    : Point2D(x,y), z(z) {}
    void setZ(int z) { this->z = z; }
    int getZ() const { return z; }
    virtual void print() const;
private:
    int z;
};
