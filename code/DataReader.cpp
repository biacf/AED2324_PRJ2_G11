//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#include "DataReader.h"

//! A \b constructor.
/*!
    Builds a <b>DataReader object</b> from the path of the .csv file to be parsed
*/
DataReader::DataReader(std::string path) {
    filename = std::move(path);
}

/**
 * @brief Extracts data from <i>airlines.csv</i>
 *
 * @return Map that associates a \b code to the <b>airline object</b> for easier lookup.
 */
std::unordered_map<std::string, Airline*> DataReader::populate_airlines() {
    std::unordered_map<std::string,Airline*> airlines;
    file.open(filename);
    std::string line;
    getline(file, line); // Ignore header

    std::string code, name, callsign, country;

    while (getline(file, line)) {
        std::istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country, ',');

        airlines.insert({code, new Airline(code,name,callsign,country)});
    }

    file.close();
    return airlines;
}

/**
 * @brief Extracts data from <i>airports.csv</i>.
 *
 * @return Map that associates a \b code to the <b>airport object</b> for easier lookup.
 */
std::unordered_map<std::string, Airport*> DataReader::populate_airports(std::unordered_map<std::pair<std::string,std::string>, std::vector<Airport *>, pair_hash>& cities) {
    std::unordered_map<std::string,Airport*> airports;
    file.open(filename);
    std::string line;
    getline(file, line); // Ignore header

    std::string code, name, city, country, latitude, longitude;

    while (getline(file, line)) {
        std::istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude, ',');

        auto* insertion = new Airport(code,name,city,country,stof(latitude),stof(longitude));
        airports.insert({code, insertion });
        cities[{city,country}].push_back(insertion);
    }

    file.close();
    return airports;
}

/**
 * @brief Extracts data from <i>flights.csv</i>
 *
 * @param airports : Map of airports.
 * @param airlines : Map of airlines
 * @return Graph that correctly represents <b>flight routes</b> between airports.
 */
FlightGraph DataReader::populate_graph(std::unordered_map<std::string, Airport*> airports, std::unordered_map<std::string, Airline*> airlines) {
    FlightGraph fgraph;
    file.open(filename);
    std::string line;
    getline(file, line); // Ignore header

    std::string source, destination, airline;

    while (getline(file, line)) {
        std::istringstream iss(line);
        getline(iss, source, ',');
        getline(iss, destination, ',');
        getline(iss, airline, ',');

        fgraph.addVertex(airports.at(source));
        fgraph.addVertex(airports.at(destination));

        airports.at(destination)->incrementIncoming();
        airports.at(source)->incrementOutgoing();

        airlines.at(airline)->addFlight();

        fgraph.addEdge(source, destination,airlines.at(airline));

    }

    file.close();
    return fgraph;
}

/**
 * @brief Extracts number of lines from <i>flights.csv</i>
 *
 * @return int representing the number of flights
 */
int DataReader::number_of_flights() {
    file.open(filename);
    std::string line;
    getline(file, line); // Ignore header
    int res = 0;
    while (getline(file, line)) {
        res++;
    }
    file.close();
    return res;
}