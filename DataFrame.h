//
// Created by fox on 3/21/20.
//

#ifndef PLAGUEINC_DATAFRAME_H
#define PLAGUEINC_DATAFRAME_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "GraphicsDependicies.h"


//enum countryState{
//    Calm,
//    Unquit,
//    Quarantine,
//    Curfew
//};

struct countryPeople{
    long double     total = 0,
                    suspected = 0,
                    infected = 0,
                    exposed = 0,
                    dead = 0,
                    recovered = 0;
    countryPeople(long double a = 0, long double b = 0, long double c = 0, long double d = 0, long double e = 0, long double f = 0): total(a), suspected(b), infected(c), exposed(d), recovered(e), dead(f){}
    countryPeople operator+=(const countryPeople _exp){
        this->total+=_exp.total;
        this->suspected+=_exp.suspected;
        this->infected+=_exp.infected;
        this->exposed+=_exp.exposed;
        this->recovered+=_exp.recovered;
        this->dead+=_exp.dead;
    }
};

class DataFrame{
private:
    std::vector<std::vector<std::string>> df;
    std::vector<countryPeople> stats;
    std::vector<std::string> states;
    int columns, rows;

public:
    DataFrame();
    bool universalCSVReader();
    void showData();
    long long getColumn(int exp_col);

    inline countryPeople getAllStats(){
        countryPeople output;
        for(int i = 0; i < stats.size(); i++){
            output.suspected+=stats[i].suspected;
            output.recovered+=stats[i].recovered;
            output.exposed+=stats[i].exposed;
            output.infected+=stats[i].infected;
            output.dead+=stats[i].dead;
        }
        return output;
    }
    inline countryPeople getCountryPeople(int country_ID){
        return stats[country_ID];
    }
    inline std::string getCountryState(int country_ID){
        return states[country_ID];
    }
    inline std::string getCountryName(int country_ID){
        return df[country_ID][0];
    }

    std::vector<int> getColumnAsVI(int exp_col);
    std::string getData( int exp_row, int exp_col);
    std::vector<std::vector<std::string>> getFrame(){return df;}
};

#endif //PLAGUEINC_DATAFRAME_H
