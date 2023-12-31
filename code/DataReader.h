//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#ifndef AED2324_PRJ2_G11_DATAREADER_H
#define AED2324_PRJ2_G11_DATAREADER_H


#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "FlightGraph.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class DataReader {
private:
    std::string filename; /*!< Path to the .csv file*/
    std::ifstream file; /*!< ifstream object */
public:
    explicit DataReader(std::string path);
    std::unordered_map<std::string, Airline*> populate_airlines();
    std::unordered_map<std::string, Airport*> populate_airports(std::unordered_map<std::pair<std::string,std::string>, std::vector<Airport *>, pair_hash>& cities);
    FlightGraph populate_graph(std::unordered_map<std::string, Airport*> airports, std::unordered_map<std::string, Airline*> airlines);
    int number_of_flights();
};


#endif //AED2324_PRJ2_G11_DATAREADER_H
