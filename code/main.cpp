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

    std::cout << "Welcome to the L.EIC2324 Flight Management Guide!" << std::endl;
    std::cout << "How can we help you?" << std::endl;
    while(true){
        char op;
        std::cout << "1 - Statistics" << std::endl;
        std::cout << "2 - Best Flight" << std::endl;
        std::cout << "3 - Exit" << std::endl;
        std::cin >> op;
        while((op < '1' || op > '3') || !isdigit(op)){
            std::cin >> op;
        }
        switch(op){
            case '1':
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
                std::cout << "k. Essential Airports" << std:: endl; //get articulation points

                std::cin >> op;

                while((op < 'a' || op > 'k') || !isalpha(op)){
                    std::cin >> op;
                }
                // do a switch OR create an exterior function to deal with it just to avoid crowding this function
                // when prompting for input CHECK IF THE INPUT IS VALID... ex: if it's an airport, look it up in the map...
                // maybe create functions for some prompts in the FlightGraph class
                break;
            case '2':
                std::string source, destination;
                std::cout << "Source: ";
                std::cin >> source;
                std::cout << "Destination: ";
                std::cin >> destination;

                //check if valid
                // idk if to prompt user for input style or try to figure it out from input
                break;
            case '3':
                return 0;
        }

        std::cout << "Anything else?" << std::endl;
    }
}
