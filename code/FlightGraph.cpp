//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#include <algorithm>
#include <queue>
#include <map>
#include <unordered_map>
#include <stack>
#include <iostream>
#include "FlightGraph.h"

//! A \b constructor.<BR><BR>
/*!
  Builds a <b>Flight Graph Vertex</b> object from an \b airport object.
*/
FlightGraphV::FlightGraphV(Airport* airport) {
    this->airport = airport;
    this->code = airport->getCode();
    visited = false;
}

/**
 * @brief Adds outgoing \b trip (<i>edge</i>) to airport. <BR><BR>
 *
 * Adds an <b>outgoing trip</b> that connects the <b>source airport</b> and the <b>destination airport</b>, performed by a certain \b airline.
 *
 * @param dest : Destination airport code.
 * @param airline : Airline that performs the connection.
 */
void FlightGraphV::addEdge(FlightGraphV *dest, Airline* airline) {
    FlightGraphE edge(dest, airline);

    //have to check when making graph undirected (articulation point calculation) , as it doesn't make sense to double existing edges
    if(std::find(flights.begin(), flights.end(), edge) == flights.end()){
        flights.push_back(edge);
    }
    if (std::find(flights_from_airline.begin(), flights_from_airline.end(), airline) == flights_from_airline.end()) {
        flights_from_airline.emplace_back(edge);
    }
}

/**
 * @brief Removes <b>outgoing trip</b> from airport.<BR><BR>
 *
 * Removes \b trip from the vector of outgoing trips from a certain airport.<BR><BR>
 * Returns \b true if successful.<BR>
 * Returns \b false if trip wasn't in vector in the first place.
 *
 * @param d : Destination airport (vertex)
 * @return \b True if trip was successfully removed, \b false otherwise.
 */
bool FlightGraphV::removeEdgeTo(FlightGraphV *d) {
    for (auto it = flights.begin(); it != flights.end(); it++)
        if (it->getDest()  == d) {
            flights.erase(it);
            return true;
        }
    return false;
}

//! A \b constructor.<BR><BR>
/*!
  Builds a <b>Flight Graph Edge</b> (<i>Trip</i>) object from its <b>destination vertex</b> (<i>airport</i>) and <b>airline</b>.
*/
FlightGraphE::FlightGraphE(FlightGraphV *dest, Airline* airline) {
    this->dest = dest;
    this->airline = airline;
}

/**
 * @brief Operator override method for graph edges.
 *
 * Method that compares edges by the airline associated with it.
 *
 * @param pns : Airline associated with edge.
 * @return \b True if airlines are the same, \b false otherwise.
 */
bool FlightGraphE::operator==( Airline* pns) const {
    return airline == pns;
}

/**
 * @brief Operator override method for graph edges.
 *
 * Method that compares edges by checking if they have the same destination vertex and the same airline.
 *
 * @param edge : Edge to compare.
 * @return \b True if edges are the same, \b false otherwise.
 */
bool FlightGraphE::operator==(FlightGraphE edge) const {
    return (dest == edge.getDest() && airline == edge.getAirline());
}

/**
 * @brief Checks if a \b vertex exists.<BR><BR>
 *
 * From an <b>airport code</b>, finds out if said airport is in the graph.<BR><BR>
 * If \b yes, returns the <i>vertex object</i> we were looking for.<BR>
 * If \b no, returns <i>null</i>.
 *
 * @param code : Code of the airport we would like to find in graph.
 * @return \b Vertex, if it exists.
 */
FlightGraphV *FlightGraph::findVertex(const std::string &code) const {
    for (auto v : flightvSet)
        if (v->getCode() == code)
            return v;
    return nullptr;
}

/**
 * @brief Add \b airport (<i>vertex</i>) to graph. <BR><BR>
 *
 * From an <b>airport object</b>, <i>adds</i> it to graph if it doesn't already exist as a vertex in it.<BR><BR>
 * Returns \b true if the vertex wasn't already in the graph and \b false otherwise.<BR>
 *
 * @param airport : \b Airport we want to add to graph.
 * @return \b True if vertex was successfully added, \b false otherwise.
 */
bool FlightGraph::addVertex(Airport* airport) {
    if (findVertex(airport->getCode()) != nullptr)
        return false;
    flightvSet.push_back(new FlightGraphV(airport));
    return true;
}

/**
 * @brief Remove \b airport (<i>vertex</i>) from graph. <BR><BR>
 *
 * From an <b>airport code</b>, tries to <i>remove</i> it from graph.<BR><BR>
 * Returns \bfalse if it wasn't in the graph in the first place and \btrue otherwise.
 *
 * @param code : Code of the airport we want to <i>remove</i> from graph.
 * @return \b True if vertex was successfully removed, \b false otherwise.
 */
bool FlightGraph::removeVertex(const std::string &code) {
    for (auto it = flightvSet.begin(); it != flightvSet.end(); it++)
        if ((*it)->getCode()  == code) {
            auto v = *it;
            flightvSet.erase(it);
            for (auto u : flightvSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

/**
 * @brief Adds \b trip (<i>edge</i>) to graph. <BR><BR>
 *
 * <i>Adds</i> a \b trip from <b>source airport</b> to <b>destination airport</b> performed by a certain \b airline.<BR><BR>
 * If either airport <i>doesn't exist</i>, \b false is returned.<BR>
 * If the operation is <i>successful</i>, it returns \b true.
 *
 * @param sourc : Source airport code.
 * @param dest : Destination airport code.
 * @param airline : Airline responsible for connection.
 * @return \b True if trip (<i>edge</i>) was successfully added and \b false otherwise.
 */
bool FlightGraph::addEdge(const std::string &sourc, const std::string &dest, Airline* airline) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2,airline);
    return true;
}

/**
 * @brief Removes \b trip (<i>edge</i>) from graph.<BR><BR>
 *
 * <i>Removes</i> a \b trip from <b>source airport</b> to <b>destination airport</b>.<BR><BR>
 * If either airport <i>doesn't exist</i>, \b false is returned.<BR>
 * If the operation is <i>successful</i>, it returns \b true.
 *
 * @param sourc : Source airport code.
 * @param dest : Destination airport code.
 * @return \b True if trip (<i>edge</i>) was successfully removed and \b false otherwise.
 */
bool FlightGraph::removeEdge(const std::string &sourc, const std::string &dest) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    return v1->removeEdgeTo(v2);
}

/**
 * @brief Gets reachable destinations from X airport with Y layovers.<BR><BR>
 *
 * Auxiliary function to i. in Statistics.<BR><BR>
 * Given an <b>airport code</b>, an <i>integer value</i> that represents the <b>expected layovers</b>, and unordered sets that collect the results, returns the reachable destinations from said airport that are a certain amount of layovers away.
 *
 * @param airport_code : Airport Code.
 * @param layovers : Amount of layovers.
 * @param airports : Reachable airports.
 * @param countries : Reachable countries.
 * @param cities : Reachable cities.
 */
void FlightGraph::getDestinations(std::string airport_code, int layovers, std::unordered_set<Airport*> &airports, std::unordered_set<std::string> &countries, std::unordered_set<std::string> &cities) const {
    std::vector<Airport*> solutions;
    layovers++;
    solutions = AirportsAtDistanceXLayovers(airport_code, layovers);

    for(const auto& a : solutions){
        airports.insert(a);

        if(countries.find(a->getCountry()) == countries.end()){
            countries.insert(a->getCountry());
        }

        if(cities.find(a->getCity()) == cities.end()){
            cities.insert(a->getCity());
        }
    }
}

/**
 * @brief Get Airports that are a certain amount of layovers away. <BR><BR>
 *
 * Using \b BFS, get a vector of Airports that need a certain amount of layovers to be reached from a certain source airport.
 *
 * @param source : Source Airport
 * @param layovers : Number of layovers.
 * @return Vector of Airports that are a certain number of layovers away from source.
 */
std::vector<Airport*> FlightGraph::AirportsAtDistanceXLayovers(const std::string &source, int layovers) const {
    std::vector<Airport*> res;
    std::queue<FlightGraphV*> vers;
    std::map<std::string, int> level;

    for(auto ver: getFlightVSet()) {
        ver->setVisited(false);
    }

    FlightGraphV *srcVertex = findVertex(source);
    if(srcVertex != nullptr) {
        vers.push(srcVertex);
        srcVertex->setVisited(true);
        level[srcVertex->getCode()] = 0;

        while (!vers.empty()) {
            FlightGraphV* v = vers.front();
            vers.pop();
            int currentLevel = level[v->getCode()];

            if(currentLevel == layovers) {
                res.push_back(v->getAirport());
            }

            if(currentLevel < layovers) {
                for(auto e : v->getFlights()) {
                    FlightGraphV* adjV = e.getDest();
                    if (!adjV->isVisited()) {
                        vers.push(adjV);
                        adjV->setVisited(true);
                        level[adjV->getCode()] = currentLevel + 1;
                    }
                }
            }
        }
    }
    return res;
}

/**
 * @brief A method that identifies the graph's articulation points.<BR><BR>
 *
 * Using DFS, this method goes through the graph and identifies its <b>articulation points</b>.<BR><BR>
 * These points represent the \b airports that are essential to maintaining all air travel connected.
 *
 * @param v : Current vertex being explored.
 * @param parent : Parent vertex.
 * @param articulationPoints : Set of articulation points.
 */
void FlightGraph::dfsArt(FlightGraphV* v, FlightGraphV* parent, std::set<Airport*>& articulationPoints) {
    v->setVisited(true);
    v->setNum(index);
    v->setLow(index);
    index++;
    int children = 0;

    for (auto edge : v->getFlights()) {
        FlightGraphV* w = edge.getDest();
        if (!w->isVisited()) {
            children++;
            dfsArt(w, v, articulationPoints);
            v->setLow(std::min(v->getLow(), w->getLow()));

            if (parent == nullptr && children > 1)
                articulationPoints.insert(v->getAirport());
            if (parent != nullptr && w->getLow() >= v->getNum())
                articulationPoints.insert(v->getAirport());
        } else if (w != parent) {
            v->setLow(std::min(v->getLow(), w->getNum()));
        }
    }
}

/**
 * @brief Finds best flight from one of sources to one of destinations.<BR><BR>
 *
 * Given a vector of <b>source airports</b> and a vector of <b>destination airports</b>, finds the <b>best flight</b> or \b flights between sources and destinations. This corresponds to the ones with the least amount of layovers.
 *
 * @param sources : Vector of source airports.
 * @param destinations : Vector of destination airports.
 */
void FlightGraph::findBestFlight(std::vector<Airport *> sources, std::vector<Airport *> destinations) {
    std::unordered_map<FlightGraphV*, int> layovers;
    std::unordered_map<FlightGraphV*, std::vector<FlightGraphV*>> predecessors;
    int minLayoversToDest = INT_MAX;
    std::queue<FlightGraphV*> queue;
    std::set<FlightGraphV*> destinationVertices;

    //wrong input handling
    if (sources.empty() && destinations.empty()){
        std::cout << "Invalid Source and Destination." << std::endl;
        return;
    }
    else if(sources.empty()){
        std::cout << "Invalid Source." << std::endl;
    }
    else if(destinations.empty()){
        std::cout << "Invalid Destination." << std::endl;
    }



    // prep for BFS
    for (auto source : sources) {
        FlightGraphV* sourceVertex = findVertex(source->getCode());
        layovers[sourceVertex] = -1;
        queue.push(sourceVertex);
    }
    for (auto destination : destinations) {
        FlightGraphV* destVertex = findVertex(destination->getCode());
        destinationVertices.insert(destVertex);
    }

    // BFS
    while (!queue.empty()) {
        FlightGraphV* current = queue.front();
        queue.pop();

        for (auto edge : current->getFlights()) {
            FlightGraphV* next = edge.getDest();
            int nextLayovers = layovers[current] + 1;

            if (layovers.find(next) == layovers.end() || layovers[next] > nextLayovers) {
                layovers[next] = nextLayovers;
                predecessors[next].clear();
                predecessors[next].push_back(current);
                queue.push(next);
            }
            else if (layovers[next] == nextLayovers) {
                predecessors[next].push_back(current);
            }

            if (destinationVertices.find(next) != destinationVertices.end()) {
                if (layovers[next] < minLayoversToDest) {
                    minLayoversToDest = layovers[next];
                }
            }
        }
    }
    if(minLayoversToDest == -1){
        std::cout << "You're already at your destination!" << std::endl;
        return;
    }
    int i = 1;
    // output
    for (auto dest : destinationVertices) {
        if (layovers[dest] == minLayoversToDest) {
            printPaths(dest, predecessors, i);
        }
    }
}

/**
 * @brief Prints paths to destination.
 *
 * For each destination, prints the path to every source airport that matches the minimum number of layovers (is in the predecessor vector).
 *
 * @param destination : Destination airport being handled.
 * @param predecessors : Map associating an airport with its predecessors.
 * @param i : Makes output more readable.
 */
void FlightGraph::printPaths(FlightGraphV* destination, std::unordered_map<FlightGraphV*, std::vector<FlightGraphV*>>& predecessors, int& i) {
    std::vector<std::vector<FlightGraphV*>> allPaths;
    std::vector<FlightGraphV*> currentPath;

    findPaths(destination, predecessors, currentPath, allPaths);

    // output
    for (const auto& path : allPaths) {
        std::cout << i << ". ";
        for (const auto& vertex : path) {
            std::cout << vertex->getAirport()->getName() << " (" << vertex->getCode() << ")";
            if (vertex != path.back()) {
                std::cout << " -> ";
            }
        }
        i++;
        std::cout << "\n" << std::endl;
    }
}

/**
 * @brief Method that finds all paths that lead to a destination.
 *
 * This method finds all possible paths that lead to a certain destination by checking its predecessors.
 *
 * @param vertex : Destinations being handled.
 * @param predecessors : Map associating an airport with its predecessors.
 * @param currentPath : Path being handled.
 * @param allPaths : Vector that stores all paths reversed.
 */
void FlightGraph::findPaths(FlightGraphV* vertex, std::unordered_map<FlightGraphV*, std::vector<FlightGraphV*>>& predecessors, std::vector<FlightGraphV*>& currentPath, std::vector<std::vector<FlightGraphV*>>& allPaths) {
    currentPath.push_back(vertex);

    if (predecessors[vertex].empty()) {
        std::vector<FlightGraphV*> reversePath(currentPath.rbegin(), currentPath.rend());
        if (std::find(allPaths.begin(), allPaths.end(), reversePath) == allPaths.end()) {
            allPaths.push_back(reversePath);
        }
    }
    else {
        for (FlightGraphV* pred : predecessors[vertex]) {
            findPaths(pred, predecessors, currentPath, allPaths);
        }
    }

    currentPath.pop_back();
}
