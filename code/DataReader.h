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

/**
 * Custom hash function that allows an unordered map to have a pair as a key.
 */
struct pair_hash {
    inline std::size_t operator()(const std::pair<std::string, std::string> &v) const {
        return std::hash<std::string>()(v.first) ^ std::hash<std::string>()(v.second);
    }
};

class DataReader {
private:
    std::string filename; /*!< Path to the .csv file */
    std::ifstream file; /*!< ifstream object */
public:
    explicit DataReader(std::string path);
    std::unordered_map<std::string, Airline*> populate_airlines();
    std::unordered_map<std::string, Airport*> populate_airports(std::unordered_map<std::pair<std::string,std::string>, std::vector<Airport *>, pair_hash>& cities);
    FlightGraph populate_graph(std::unordered_map<std::string, Airport*> airports, std::unordered_map<std::string, Airline*> airlines);
    int number_of_flights();
};


#endif //AED2324_PRJ2_G11_DATAREADER_H
