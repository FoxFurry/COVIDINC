//
// Created by foxfurry on 5/17/20.
//

#ifndef PLAGUEINC_SEIRD_H
#define PLAGUEINC_SEIRD_H

#include <cmath>
#include "DataFrame.h"

#define BETA 0.219f
#define GAMMA 0.0102f
#define MU 0.00113f
#define KAPPA 1/3.f
#define PSI 0.6f

#define ALPHA 0.5f
#define KAPPA_ZERO 0.1f

static inline double PhiPolynomial(double I, double E){
    return exp(-ALPHA*pow((I+PSI*E), KAPPA_ZERO));
}

static inline double PhiLinear(double t, double n){
    return KAPPA_ZERO * exp(-ALPHA*t);
}

static inline countryPeople SEIRDDX(countryPeople x, double betta, double psi, double kappa, double gamma, double mu, double Phi(double, double)){
    double N = x.total;
    countryPeople dx;
    dx.suspected = -betta * (x.suspected * (x.infected + psi * x.exposed) * Phi(x.infected, x.exposed)) / N; //
    dx.exposed = betta * (x.suspected * (x.infected + psi * x.exposed) * Phi(x.infected, x.exposed)) / N - kappa * x.exposed; //
    dx.infected = kappa * x.exposed - gamma * x.infected - mu * x.dead;
    dx.recovered = gamma * x.infected;
    dx.dead = mu * x.dead;
    return dx;
}

#endif //PLAGUEINC_SEIRD_H
