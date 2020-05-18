//
// Created by fox on 3/25/20.
//

#include "Trigonometry.h"

vec toVec(point a, point b){
    return vec(b.x - a.x, b.y - a.y);
}

double norm_sq(vec v){
    return v.x * v.x + v.y * v.y;
}

double dot(vec a, vec b){
    return (a.x * b.x + a.y * b.y);
}

double cross(vec a, vec b){
    return a.x * b.y - a.y * b.x;
}

double angle(point a, point o, point b){
    vec oa = toVec(o, a), ob = toVec(o,b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

bool ccw(point p, point q, point r){
    return cross(toVec(p,q), toVec(p, r)) > 0;
}

bool inPolygon(point pt, const std::vector<point> &P){
    if ((int)P.size()==0)return false;
    double sum = 0;
    for(int i = 0; i < (int)P.size(); i++){
        if(i == (int)P.size()-1){
            if(ccw(pt, P[i], P[0]))
                sum += angle(P[i], pt, P[0]);
            else sum -= angle(P[i], pt, P[0]);
        }
        else {
            if (ccw(pt, P[i], P[i + 1]))
                sum += angle(P[i], pt, P[i + 1]);
            else sum -= angle(P[i], pt, P[i + 1]);
        }
    }
    return fabs(fabs(sum) - 2*M_PIl) < EPS;
}