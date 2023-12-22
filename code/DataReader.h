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

class DataReader {
private:
    std::string filename; /*!< Path to the .csv file*/
    std::ifstream file; /*!< ifstream object */
public:
    explicit DataReader(std::string path);
    std::map<std::string, Airline> populate_airlines();
    std::map<std::string, Airport> populate_airports();
    FlightGraph populate_graph(std::map<std::string, Airport> airports, std::map<std::string, Airline> airlines);
};


#endif //AED2324_PRJ2_G11_DATAREADER_H
