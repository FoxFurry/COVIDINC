//
// Created by fox on 3/25/20.
//

#ifndef PLAGUEINC_TRIGONOMETRY_H
#define PLAGUEINC_TRIGONOMETRY_H

#include <cmath>
#include "GraphicsDependicies.h"

#define EPS 1e-9


struct point{
    double x,y;
    point() {x = y = 0.0;}
    point (double _x, double _y) : x(_x), y(_y) {}

    bool operator < (point other) const {
        if(fabs(x-other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator == (point other) const {
        return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS));
    }
};

struct vec {
    double x,y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};


vec toVec(point a, point b);

double norm_sq(vec v);

double dot(vec a, vec b);

double cross(vec a, vec b);

double angle(point a, point o, point b);

bool ccw(point p, point q, point r);

bool inPolygon(point pt, const std::vector<point> &P);

#endif //PLAGUEINC_TRIGONOMETRY_H
