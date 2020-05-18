//
// Created by fox on 3/21/20.
//

#include "DataFrame.h"


bool is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

DataFrame::DataFrame() {
    df.clear();
    columns = 0;
    rows = 0;
}

bool DataFrame::universalCSVReader() {
    std::ifstream input1, input2;

    input1.open(PTH_CSV_PART_1, std::ios::in);
    if (!input1)
        throw(PTH_CSV_PART_1);

    input2.open(PTH_CSV_PART_2, std::ios::in);
    if (!input2)
        throw(PTH_CSV_PART_2);

    std::string temp;
    for (int i = 0; input1 >> temp; i++) {
        std::string data_cell, read_row;
        rows++;
        df.resize(rows);
        getline(input1, read_row);
        std::stringstream s_stream_input1(read_row);
        for (int r_exp = 0; getline(s_stream_input1, data_cell, ';'); r_exp++) {
            if (r_exp == 0) {
                data_cell.erase(std::remove_if(data_cell.begin(), data_cell.end(),
                                               [](auto const &c) -> bool { return c < 30 || c > 122; }),
                                data_cell.end());
                data_cell.erase(data_cell.begin());
            } else
                data_cell.erase(std::remove_if(data_cell.begin(), data_cell.end(),
                                               [](auto const &c) -> bool { return c < 40 || c > 122; }),
                                data_cell.end());

            df[i].resize(r_exp + 1);
            df[i][r_exp] = data_cell;
            if(r_exp==1)stats.push_back(countryPeople(0,std::stoi(data_cell), 0, 0, 0, 0));
        }
        if (df[i].size() > columns)columns = df[i].size();
    }
    temp.clear();
    for (int i = rows; input2 >> temp; i++) {
        std::string data_cell, read_row;
        rows++;
        df.resize(rows);
        getline(input2, read_row);
        std::stringstream s_stream_input2(read_row);

        for (int r_exp = 0; getline(s_stream_input2, data_cell, ';'); r_exp++) {
            if (r_exp == 0) {
                data_cell.erase(std::remove_if(data_cell.begin(), data_cell.end(),
                                               [](auto const &c) -> bool { return c < 30 || c > 122; }),
                                data_cell.end());
                data_cell.erase(data_cell.begin());
            } else
                data_cell.erase(std::remove_if(data_cell.begin(), data_cell.end(),
                                               [](auto const &c) -> bool { return c < 40 || c > 122; }),
                                data_cell.end());

            df[i].resize(r_exp + 1);
            df[i][r_exp] = data_cell;
            if(r_exp==1)stats.push_back(countryPeople(0,std::stoi(data_cell), 0, 0, 0, 0));
        }
        if (df[i].size() > columns)columns = df[i].size();

    }
    states.assign(df.size(), "Calm");
    return true;
}

void DataFrame::showData() {
    for (int i = 0; i < rows; i++) {
        printf("%-5d", i);
        for (int g = 0; g < df[i].size(); g++) {
            printf("%-20s", df[i][g].c_str());
        }
        printf("\n");
    }
}

std::string DataFrame::getData(int exp_row, int exp_col) {
    if (exp_row < df.size())
        if (exp_col < df[exp_row].size())
            return df[exp_row][exp_col];
    return "";
}

long long DataFrame::getColumn(int exp_col) {
    if(!is_number(df[0][exp_col]))return 0;
    long long output = 0;
    for(int i = 0; i < df.size(); i++)
        output += std::stoi(df[i][exp_col]);
    return output;
}

