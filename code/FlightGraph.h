//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#ifndef AED2324_PRJ2_G11_FLIGHTGRAPH_H
#define AED2324_PRJ2_G11_FLIGHTGRAPH_H

#include <vector>
#include <unordered_set>
#include <set>
#include "Airport.h"
#include "Airline.h"

class FlightGraphE;
class FlightGraphV;
class FlightGraph;

class FlightGraphV{
private:
    std::string code; /*!< Airport code for lookup purposes*/
    Airport* airport; /*!< Airport object associated with vertex */
    std::vector<FlightGraphE> flights; /*!< Vector of flights outgoing from airport */
    std::vector<FlightGraphE> flights_from_airline; /*!< Vector of airlines responsible for outgoing flights */
    bool visited; /*!< For traversal purposes */
    bool processing; /*!< For traversal purposes */
    int num, low; /*!< For finding articulation points */

public:
    void addEdge(FlightGraphV *dest, Airline* airline); /*!< Add flight */
    bool removeEdgeTo(FlightGraphV *d); /*!< Remove flight */
    FlightGraphV(Airport* airport);
    bool isVisited(){return visited;} /*! A getter method @return boolean value */
    void setVisited(bool value){visited = value;} /*! A setter method */
    bool isProcessing(){return processing;} /*! A getter method @return boolean value */
    void setProcessing(bool value){processing = value;} /*! A setter method */
    void setNum(int num){this->num = num;} /*! A setter method */
    int getNum(){return num;} /*! A getter method @return num parameter */
    void setLow(int num){low = num;} /*! A setter method */
    int getLow(){return low;}/*! A getter method @return low parameter */
    std::vector<FlightGraphE> getFlights(){return flights;} /*! A getter method @return Vector of outgoing flights */
    std::string getCode(){return code;} /*! A getter method @return Airport code for lookup purposes */
    Airport* getAirport(){return airport;} /*! A getter method @return Airport associated with vertex */
    int getOutgoingF(){return flights.size();} /*! A getter method @return Number of outgoing flights from airport */
    int getOutgoingA(){return flights_from_airline.size();} /*! A getter method @return Number of airlines responsible for outgoing flights */
};

class FlightGraphE{
private:
    FlightGraphV* dest; /*!< Flight destination vertex */
    Airline* airline; /*!< Airline responsible for flight */
public:
    FlightGraphE(FlightGraphV* dest, Airline* airline);
    FlightGraphV* getDest(){return dest;} /*! A getter method @return Flight destination */
    Airline* getAirline(){return airline;} /*! A getter method @return Airline */

    bool operator==(Airline* pns) const;
};

class FlightGraph {
private:
    std::vector<FlightGraphV*> flightvSet; /*!< Vector of airports */
    int index; /*< Field to help find articulation points */
public:
    FlightGraph()= default; /*! Default constructor */
    FlightGraphV *findVertex(const std::string &code) const;
    int getNumVertex() const{return flightvSet.size();} /*! A getter method @return Number of airports in graph */
    bool addVertex(Airport* airport);
    bool removeVertex(const std::string &code);
    bool addEdge(const std::string &sourc, const std::string &dest, Airline* airline) const;
    bool removeEdge(const std::string &sourc, const std::string &dest);
    void setIndex(int i){index = i;}/*! A setter method */
    int getIndex(){return index;}/*!A getter method @return Index */
    std::vector<FlightGraphV*> getFlightVSet() const{return flightvSet;} /*! A getter method @return Vector of airport vertexes */
    void getDestinations(std::string airport_code, int layovers, std::unordered_set<Airport*> &airports, std::unordered_set<std::string> &countries, std::unordered_set<std::string> &cities);
    std::vector<Airport *> AirportsAtDistanceXLayovers(const std::string &source, int layovers) const;
    void dfsArt(FlightGraphV *v, FlightGraphV *parent, std::set<Airport*> &articulationPoints);
};


#endif //AED2324_PRJ2_G11_FLIGHTGRAPH_H
