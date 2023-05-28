#ifndef DATA_H
#define DATA_H

#include <cmath>
#include <iostream>
#include <tuple>


struct Point {
    double x, y;

    double distance(Point &that) {
        double dx = this->x - that.x;
        double dy = this->y - that.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    friend std::ostream& operator<<(std::ostream& os, Point p) {
        return os << '(' << p.x << ',' << p.y << ')';
    }
    
    friend bool operator== (const Point& p1, const Point& p2) { return p1.x == p2.x && p1.y == p2.y; }
    friend bool operator!= (const Point& p1, const Point& p2) { return p1.x != p2.x || p1.y != p2.y; }

    friend bool operator< (const Point& p1, const Point& p2) { return p1.x != p2.x ? p1.x < p2.x : p2.y < p2.y; };
    friend bool operator> (const Point& p1, const Point& p2) { return p1.x != p2.x ? p1.x > p2.x : p2.y > p2.y; };

    friend bool operator<= (const Point& p1, const Point& p2) { return p1.x != p2.x ? p1.x <= p2.x : p2.y <= p2.y; };
    friend bool operator>= (const Point& p1, const Point& p2) { return p1.x != p2.x ? p1.x >= p2.x : p2.y >= p2.y; };
};

struct Line {
    Point a, b;

    double distance(Point &p) {
        double d = a.distance(b);
        return std::abs((b.x - a.x) * (a.y - p.y) - (a.x - p.x) * (b.y - a.y)) / d;
    }

    double side(Point &p) {
        double c1 = a.y - b.y;
        double c2 = b.x - a.x;
        double c3 = b.y * a.x - b.x * a.y;
        return c1*p.x + c2*p.y + c3; 
    }

    friend std::ostream& operator<<(std::ostream& os, Line l) {
        return os << l.a << " -- " << l.b;
    }
};

struct Range {
    size_t i, j;
    friend std::ostream& operator<<(std::ostream& os, Range r) {
        return os << '[' << r.i << ',' << r.j << ')';
    }

    inline size_t n() const { return j - i; }

    friend bool operator== (const Range& r1, const Range& r2) { return r1.i == r2.i && r1.j == r2.j; }
    friend bool operator!= (const Range& r1, const Range& r2) { return r1.i != r2.i || r1.j != r2.j; }

    friend bool operator< (const Range& r1, const Range& r2) {
        return std::make_tuple(r1.n(), r1.i, r1.j) < std::make_tuple(r2.n(), r2.i, r2.j);
    }
    friend bool operator> (const Range& r1, const Range& r2) {
        return std::make_tuple(r1.n(), r1.i, r1.j) > std::make_tuple(r2.n(), r2.i, r2.j);
    }
    friend bool operator<= (const Range& r1, const Range& r2) {
        return std::make_tuple(r1.n(), r1.i, r1.j) <= std::make_tuple(r2.n(), r2.i, r2.j);
    }
    friend bool operator>= (const Range& r1, const Range& r2) {
        return std::make_tuple(r1.n(), r1.i, r1.j) >= std::make_tuple(r2.n(), r2.i, r2.j);
    }
};


#endif