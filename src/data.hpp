#ifndef DATA_H
#define DATA_H

#include <cmath>
#include <iostream>


struct Point {
    double x, y;

    double distance(Point &that) {
        double dx = this->x - that.x;
        double dy = this->y - that.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    friend std::ostream& operator<<(std::ostream& os, Point &p) {
        return os << '(' << p.x << ',' << p.y << ')';
    }
};

struct Line {
    Point a, b;

    double distance(Point &p) {
        double d = a.distance(b);
        return std::abs((b.x - a.x) * (a.y - p.y) - (a.x - p.x)*(b.y - a.y)) / d;
    }

    double side(Point &p) {
        double c1 = a.y - b.y;
        double c2 = b.x - a.x;
        double c3 = b.y * a.x - b.x * a.y;
        return c1*p.x + c2*p.y + c3; 
    }
};

struct Range {
    int i, j;
    friend std::ostream& operator<<(std::ostream& os, Range &r) {
        return os << '[' << r.i << ',' << r.j << ')';
    }
};


#endif