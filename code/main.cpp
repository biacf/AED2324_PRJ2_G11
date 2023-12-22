#include <iostream>
#include <iostream>
#include "DataReader.h"
int main() {
    std::map<std::string, Airline> airlines;
    std::map<std::string, Airport> airports;
    FlightGraph flights;

    //distribute data
    DataReader airline_info("../code/dataset/airlines.csv");
    airlines = airline_info.populate_airlines();
    DataReader airport_info("../code/dataset/airports.csv");
    airports = airport_info.populate_airports();
    DataReader flight_info("../code/dataset/flights.csv");
    flights = flight_info.populate_graph(airports,airlines);

}
