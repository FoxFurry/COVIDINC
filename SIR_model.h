//
// Created by fox on 2/24/20.
//

#ifndef PLAGUEINC_SIR_MODEL_H
#define PLAGUEINC_SIR_MODEL_H

#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>

using namespace boost::numeric::odeint;

const double b = 0.1; // recovery coefficient
const double a = 0.005; // transmisiion coefficient (depends on conditions)

//const double b = 0.1;
//const double a = 0.007;

typedef boost::array< double , 3 > state_type;

void sir( const state_type &x , state_type &dxdt , double t );

void write_sir(const state_type &x , const double t );

#endif //PLAGUEINC_SIR_MODEL_H

//    output.open("sir_out.csv");
//    output << "Time, S, I, R\n";
//    state_type x = {10, 0.01, 0.01}; // initial conditions
//    integrate(sir, x, 0.0, 100.0, 0.1, write_sir);