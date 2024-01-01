//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#ifndef AED2324_PRJ2_G11_AIRLINE_H
#define AED2324_PRJ2_G11_AIRLINE_H


#include <string>

class Airline {
private:
    std::string code; /*!< Airline code */
    std::string name; /*!< Airline name */
    std::string callsign; /*!< Airline callsign */
    std::string country; /*!< Airline country */
    int flights; /*!< Number of flights */
public:
    Airline()= default; /*! Default constructor */
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    void addFlight(){flights++;} /*! A method that increments the number of flights */
    /*! A getter method @return Airline code */
    std::string getCode(){return code;}
    /*! A getter method @return Airline name */
    std::string getName(){return name;}
    /*! A getter method @return Airline callsign */
    std::string getCallsign(){return callsign;}
    /*! A getter method @return Airline country */
    std::string getCountry(){return country;}
    /*! A getter method @return Number of flights */
    int getFlights(){return flights;}

    bool operator==(const Airline &pns) const;
};


#endif //AED2324_PRJ2_G11_AIRLINE_H
