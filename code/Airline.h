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
public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    /*! A getter method @return Airline code */
    std::string getCode(){return code;}
    /*! A getter method @return Airline name */
    /*! A getter method @return Airline callsign */
    /*! A getter method @return Airline country */
};


#endif //AED2324_PRJ2_G11_AIRLINE_H
