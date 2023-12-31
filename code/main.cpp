#include <iostream>
#include "DataReader.h"
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>


/**
 * @brief Degrees to Radians <BR><BR>
 *
 * Method transforms a degree value into radians to calculate distances between coordinates.
 *
 * @param deg : Degree value.
 * @return Radians value.
 */
float deg2rad(float deg) {
    return deg * M_PI / 180.0;
}

/**
 * @brief Method that calculates distance between two coordinates.<BR><BR>
 *
 * Method that takes two coordinates and calculates the distance between them using the Harversine Distance Formula.
 *
 * @param lat1 : Latitude of coordinate 1.
 * @param lon1 : Longitude of coordinate 1.
 * @param lat2 : Latitude of coordinate 2.
 * @param lon2 : Longitude of coordinate 2.
 * @return Distance between coordinate 1 and coordinate 2.
 */
float haversineDistance(float lat1, float lon1, float lat2, float lon2) {
    float dLat = deg2rad(lat2 - lat1);
    float dLon = deg2rad(lon2 - lon1);
    lat1 = deg2rad(lat1);
    lat2 = deg2rad(lat2);

    float a = sin(dLat / 2) * sin(dLat / 2) +
              sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371.0 * c;
}

/**
 * @brief Find airports in 100km radius of coordinates.
 * @param lat : Location latitude.
 * @param lon : Location longitude.
 * @param airports : Map code <-> airport.
 * @return Vector of airports.
 */
std::vector<Airport*> findAirportsByCoords(float lat, float lon, std::unordered_map<std::string, Airport *> airports) {
    std::vector<Airport *> res;
    float dist;
    for(auto a : airports){
        dist = haversineDistance(lat, lon, a.second->getLatitude(), a.second->getLongitude());
        if(dist <= 100){
            res.push_back(a.second);
        }
    }

    return res;
}


int main() {
    std::unordered_map<std::string, Airline *> airlines;
    std::unordered_map<std::string, Airport *> airports;
    std::unordered_map<std::string, std::vector<Airport *>> cities;
    FlightGraph flights;
    int number_of_flights;

    //distribute data
    DataReader airline_info("../code/dataset/airlines.csv");
    airlines = airline_info.populate_airlines();
    DataReader airport_info("../code/dataset/airports.csv");
    airports = airport_info.populate_airports(cities);
    DataReader flight_info("../code/dataset/flights.csv");
    flights = flight_info.populate_graph(airports, airlines);
    number_of_flights = flight_info.number_of_flights();

    std::cout << "Welcome to the L.EIC2324 Flight Management Guide!" << std::endl;
    std::cout << "How can we help you?" << std::endl;
    while (true) {
        char op;
        std::cout << "1 - Statistics" << std::endl;
        std::cout << "2 - Best Flight" << std::endl;
        std::cout << "3 - Exit" << std::endl;
        std::cin >> op;
        while ((op < '1' || op > '3') || !isdigit(op)) {
            std::cin >> op;
        }
        switch (op) {

            case '1': {
                std::cout << "a. Total Airports" << std::endl; // easy... airports.size()
                std::cout << "b. Total Flights" << std::endl; //easy from the graph but not efficient probably... maybe do a line count for the flights.csv
                std::cout << "c. Outgoing Flights From X Airport" << std::endl; // easy
                std::cout << "d. Airlines Flying From X Airport" << std::endl; // this is relatively easy
                std::cout << "e. Outgoing Flights From X City" << std::endl; // again maybe create a City Class containing airports but idk how that would work
                std::cout << "f. Total Flights From X Airline" << std::endl; //we probably need to create another graph OR another data structure to store this info ????
                std::cout << "g. Reachable Countries From X Airport" << std::endl; // easy
                std::cout << "h. Reachable Countries From X City" << std::endl; // maybe create a City Class.... still thinking about this
                std::cout << "i. Total Destinations From X Airport" << std::endl; //prompts for layovers, can be done with bfs adaptation
                std::cout << "j. Longest Trip(s)" << std::endl; // can be done with dfs i'm pretty sure
                std::cout << "k. Essential Airports" << std::endl; //get articulation points

                char statistical_op;
                std::cin >> statistical_op;

                while ((statistical_op < 'a' || statistical_op > 'k') || !isalpha(statistical_op)) {
                    std::cin >> statistical_op;
                }

                switch (statistical_op) {
                    case 'a': {
                        std::cout << "The total number of airports is " << airports.size() << std::endl;
                        break;
                    }
                    case 'b': {
                        std::cout << "The total number of flights is " << number_of_flights << std::endl;
                        break;
                    }
                    case 'c': {
                        std::string airport;
                        std::cout << "Airport: ";
                        std::cin >> airport;
                        int outgoing_flights = flights.findVertex(airport)->getOutgoingF();
                        std::cout << "The total number of outgoing flights from " << airport << " is "
                                  << outgoing_flights << std::endl;
                        break;
                    }
                    case 'd': {
                        std::string airport;
                        std::cout << "Airport: ";
                        std::cin >> airport;
                        int outgoing_airlines = flights.findVertex(airport)->getOutgoingA();
                        std::cout << "The total number of airlines with outgoing flights from " << airport << " is "
                                  << outgoing_airlines << std::endl;
                        break;
                    }
                    case 'g': {
                        std::unordered_set<std::string> destinations;
                        std::string airport_code;

                        std::cout << "Airport Code: ";
                        std::cin >> airport_code;

                        while (airports.find(airport_code) == airports.end()) {
                            std::cout << "Airport doesn't exist" << std::endl;
                            std::cin >> airport_code;
                        }

                        std::string airport_name = airports.find(airport_code)->second->getName();

                        std::vector<FlightGraphE> out = flights.findVertex(airport_code)->getFlights();
                        for (auto e: out) {
                            if (destinations.find(e.getDest()->getAirport()->getCountry()) == destinations.end()) {
                                destinations.insert(e.getDest()->getAirport()->getCountry());
                            }
                        }

                        std::cout << "You can fly to " << destinations.size() << " countries from " << airport_name
                                  << " (" << airport_code << ")" << std::endl;
                        for (const auto &d: destinations) {
                            std::cout << d << std::endl;
                        }

                        break;
                    }
                    case 'h': {
                        std::unordered_set<std::string> destinations_of_city;
                        std::string city;
                        std::cout << "City: ";
                        std::cin.ignore();
                        std::getline(std::cin, city);
                        std::cout << std::endl;
                        for(auto a : cities[city]){
                            FlightGraphV* vertex = flights.findVertex(a->getCode());
                            for(auto c : vertex->getFlights()){
                                FlightGraphV* dest = c.getDest();
                                destinations_of_city.emplace(dest->getAirport()->getCountry());
                            }
                        }
                        if (!destinations_of_city.empty()) {
                            std::cout << "You can fly to " << destinations_of_city.size() << " countries from " << city <<": "<<std::endl;
                            for (const auto &a: destinations_of_city) {
                                std::cout << a << std::endl;
                            }
                        } else {
                            std::cout << "City: " << city << " not found" << std::endl;
                        }
                        break;
                    }
                    case 'i': {
                        //unordered sets for answer
                        std::unordered_set<Airport *> reachable_airports;
                        std::unordered_set<std::string> reachable_cities;
                        std::unordered_set<std::string> reachable_countries;

                        //airport code
                        std::string airport_code;
                        std::cout << "Airport code: ";
                        std::cin >> airport_code;

                        while (airports.find(airport_code) == airports.end()) {
                            std::cout << "Airport doesn't exist" << std::endl;
                            std::cin >> airport_code;
                        }

                        // layovers (min 0)
                        int layovers;
                        std::cout << "How many layovers (if any)?: ";
                        std::cin >> layovers;

                        while (layovers < 0) {
                            std::cin >> layovers;
                        }

                        flights.getDestinations(airport_code, layovers, reachable_airports, reachable_countries,reachable_cities);

                        std::cout << "\nAirport, City, Country\n" << std::endl;

                        for (const auto &a: reachable_airports) {
                            std::cout << a->getName() << " (" << a->getCode() << ")" << ", " << a->getCity() << ", "
                                      << a->getCountry() << std::endl;
                        }

                        std::cout << "You can reach " << reachable_airports.size() << " airports, "
                                  << reachable_countries.size() << " countries and " << reachable_cities.size()
                                  << " cities from " << airports.find(airport_code)->second->getName() << " ("
                                  << airport_code << ")" << std::endl;
                        break;
                    }
                    case 'j': {
                        std::cout << "STARTING J" << std::endl;
                        int max = 0;
                        std::set<std::pair<FlightGraphV *, FlightGraphV *>> biggest_paths;

                        for (auto startVertex: flights.getFlightVSet()) {
                            for (auto a: flights.getFlightVSet()) {
                                a->setVisited(false);
                            }

                            std::queue<std::pair<int, FlightGraphV *>> num_vertice;
                            num_vertice.emplace(0, startVertex);

                            while (!num_vertice.empty()) {
                                int stops = num_vertice.front().first;
                                FlightGraphV *current = num_vertice.front().second;
                                num_vertice.pop();

                                if (!current->isVisited()) {
                                    current->setVisited(true);

                                    for (FlightGraphE edge: current->getFlights()) {
                                        FlightGraphV *nextVertex = edge.getDest();
                                        if (!nextVertex->isVisited()) {
                                            num_vertice.emplace(stops + 1, nextVertex);
                                        }
                                    }
                                }

                                if (stops > max) {
                                    max = stops;
                                    biggest_paths.clear();
                                    biggest_paths.emplace(startVertex, current);
                                } else if (stops == max) {
                                    biggest_paths.emplace(startVertex, current);
                                }
                            }
                        }
                        if (!biggest_paths.empty()) {
                            std::cout << "Maximum number of stops: " << max << std::endl;
                            std::cout << "Starting and Ending vertices for the longest trip(s):" << std::endl;
                            for (const auto &path: biggest_paths) {
                                std::cout << path.first->getAirport()->getCode() << " - "
                                          << path.second->getAirport()->getCode() << std::endl;
                            }
                        }
                        break;
                    }
                    case 'k':{
                        std::set<Airport*> essential;
                        flights.setIndex(0);

                        //set up for articulation point lookup
                        for(auto v : flights.getFlightVSet()){
                            v->setVisited(false);
                            v->setNum(-1);
                            v->setLow(-1);
                        }

                        for (auto v: flights.getFlightVSet()){
                            if(!v->isVisited()){
                                flights.dfsArt(v, nullptr, essential);
                            }
                        }

                        //output
                        std::cout << "The essential airports are:" << std::endl;

                        for(auto a: essential){
                            std::cout << a->getName() << " (" << a->getCode() << ") " << std::endl;
                        }

                        std::cout << "In total there are " << essential.size() << " essential airports" << std::endl;
                    }
                    default:{
                        break;
                    }
                }


//                int max = 0;
//                Airport* start;
//                Airport* end;
//                std::vector<std::pair<Airport*,Airport*>> pairs;
//
//                for(auto v1 : flights.getFlightVSet()){
//                    std::queue<std::pair<int, FlightGraphV*>> q;
//                    for (auto a: flights.getFlightVSet()) {
//                        a->setVisited(false);
//                    }
//                    q.emplace(0,v1);
//                    v1->setVisited(true);
//                    while(!q.empty()){
//                        FlightGraphV* tocheck = q.front().second;
//                        for(FlightGraphE e : tocheck->getFlights()){
//                            FlightGraphV *v = e.getDest();
//                            if(!v->isVisited()){
//                                v->setVisited(true);
//                                if(q.front().first + 1 > max){
//                                    max = q.front().first + 1;
//                                    start = v1->getAirport();
//                                    end = v->getAirport();
//                                    pairs.clear();
//                                    pairs.emplace_back(start,end);
//                                }
//                                else if(q.front().first + 1 == max){
//                                    start = v1->getAirport();
//                                    end = v->getAirport();
//                                    pairs.emplace_back(start,end);
//                                }
//                                q.emplace(q.front().first + 1, v);
//                            }
//                        }
//                        q.pop();
//                    }
//                }
//                if (!pairs.empty()) {
//                    std::cout << "Maximum number of stops: " << max << std::endl;
//                    std::cout << "Starting and Ending vertices for the longest trip(s):" << std::endl;
//                    for (const auto& path : pairs) {
//                        std::cout << path.first->getCode()<< " - " << path.second->getCode() << std::endl;
//                    }
//                }
//                break;}



                // do a switch OR create an exterior function to deal with it just to avoid crowding this function
                // when prompting for input CHECK IF THE INPUT IS VALID... ex: if it's an airport, look it up in the map...
                // maybe create functions for some prompts in the FlightGraph class


                break;
            }
            case '2': {
                std::cout << "Welcome to Best Flight Finder!\n" << std::endl;

                std::string input;
                float lat, lon;
                char option;

                std::vector<Airport*> sources;
                std::vector<Airport*> destinations;

                std::cout << "Source is: " << std::endl;
                std::cout << "1. Airport Code" << std::endl;
                std::cout << "2. Airport Name" << std::endl;
                std::cout << "3. City" << std::endl;
                std::cout << "4. Coordinates"  << std::endl;
                std::cout << "Input Style: ";
                std::cin >> option;
                while(option < '1' || option > '4'){
                    std::cout << "Enter valid style: " << std::endl;
                    std::cin >> option;
                }

                switch(option) {
                    case '1':
                        std::cout << "Source code: ";
                        std::cin >> input;
                        while(airports.find(input) == airports.end()){
                            std::cout << "Enter valid code: " << std::endl;
                            std::cin >> input;
                        }

                        sources.push_back(airports.find(input)->second);
                        break;
                    case '2':
                        std::cout << "Source airport name: ";
                        std::cin.ignore();
                        std::getline(std::cin, input);
                        for(auto a : airports){
                            if(a.second->getName() == input){
                                sources.push_back(a.second);
                            }
                        }
                        break;
                    case '3':
                        std::cout << "Source city: ";
                        std::cin.ignore();
                        std::getline(std::cin, input);
                        sources = cities[input];
                        break;
                    case '4':
                        std::cout << "Source latitude: ";
                        std::cin >> lat;
                        std::cout << "Source longitude: ";
                        std::cin >> lon;
                        sources = findAirportsByCoords(lat, lon, airports);
                        break;
                    default:
                        break;
                }

                std::cout << "Destination is: " << std::endl;
                std::cout << "1. Airport Code" << std::endl;
                std::cout << "2. Airport Name" << std::endl;
                std::cout << "3. City" << std::endl;
                std::cout << "4. Coordinates"  << std::endl;
                std::cout << "Input Style: ";
                std::cin >> option;
                while(option < '1' || option > '4'){
                    std::cout << "Enter valid style: ";
                    std::cin >> option;
                }


                switch(option) {
                    case '1':
                        std::cout << "Destination code: ";
                        std::cin >> input;
                        while(airports.find(input) == airports.end()){
                            std::cout << "Enter valid code: " << std::endl;
                            std::cin >> input;
                        }
                        destinations.push_back(airports.find(input)->second);
                        break;
                    case '2':
                        std::cout << "Destination airport name: ";
                        std::cin.ignore();
                        std::getline(std::cin, input);
                        for(auto a : airports){
                            if(a.second->getName() == input){
                                destinations.push_back(a.second);
                            }
                        }
                        break;
                    case '3':
                        std::cout << "Destination city: ";
                        std::cin.ignore();
                        std::getline(std::cin, input);
                        destinations = cities[input];
                        break;
                    case '4':
                        std::cout << "Destination latitude: ";
                        std::cin >> lat;
                        std::cout << "Destination longitude: ";
                        std::cin >> lon;
                        sources = findAirportsByCoords(lat, lon, airports);
                        break;
                    default:
                        break;
                }

                flights.findBestFlight(sources, destinations);

                break;
            }
            case '3': {
                return 0;
            }
            default:{
                break;
            }
        }

        std::cout << "Anything else?" << std::endl;
    }
}



