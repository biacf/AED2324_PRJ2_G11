//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#include <algorithm>
#include "FlightGraph.h"

bool FlightGraphE::operator==(const Airline &pns) const {
    return airline == pns;
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
    return NULL;
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
bool FlightGraph::addVertex(const Airport airport) {
    if (findVertex(airport.getCode()) != NULL)
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
bool FlightGraph::addEdge(const std::string &sourc, const std::string &dest, Airline airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,airline);
    return true;
}

/**
 * @brief Removes \b trip (<i>edge</i>) from graph.<BR><BR>
 *
 * <i>Remover</i> a \b trip from <b>source airport</b> to <b>destination airport</b>.<BR><BR>
 * If either airport <i>doesn't exist</i>, \b false is returned.<BR>
 * If the operation is <i>successful</i>, it returns \b true.
 *
 * @param sourc : Source airport code.
 * @param dest : Destination airport code.
 * @return \b True if trip (<i>edge</i>) was successfully removed and \b false otherwise.
 */
bool FlightGraph::removeEdge(const std::string &sourc, const std::string &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/**
 * @brief Adds outgoing \b trip (<i>edge</i>) to airport. <BR><BR>
 *
 * Adds an <b>outgoing trip</b> that connects the <b>source airport</b> and the <b>destination airport</b>, performed by a certain \b airline.
 *
 * @param dest : Destination airport code.
 * @param airline : Airline that performs the connection.
 */
void FlightGraphV::addEdge(FlightGraphV *dest, Airline airline) {
    flights.push_back(FlightGraphE(dest, airline));
    if (std::find(flights_from_airline.begin(), flights_from_airline.end(), airline) == flights_from_airline.end()) {
        flights_from_airline.push_back(FlightGraphE(dest, airline));
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

//! A \b constructor.
/*!
  Builds a <b>Flight Graph Vertex</b> object from an \b airport object.
*/
FlightGraphV::FlightGraphV(Airport airport) {
    this->airport = airport;
    this->code = airport.getCode();
}

//! A \b constructor.
/*!
  Builds a <b>Flight Graph Edge</b> (<i>Trip</i>) object from its <b>destination vertex</b> (<i>airport</i>) and <b>airline</b>.
*/
FlightGraphE::FlightGraphE(FlightGraphV *dest, Airline airline) {
    this->dest = dest;
    this->airline = airline;
}
