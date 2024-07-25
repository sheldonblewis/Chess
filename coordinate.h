#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
private:
    int x, y;

public:
    Coordinate(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
};

#endif // COORDINATE_H
