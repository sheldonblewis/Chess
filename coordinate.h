#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
private:
    int x, y;

public:
    Coordinate() : x(-1), y(-1) {}
    Coordinate(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    bool operator==(const Coordinate& other) const;
};

#endif // COORDINATE_H
