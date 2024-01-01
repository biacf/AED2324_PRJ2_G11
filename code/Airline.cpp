//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#include "Airline.h"
//! A constructor.<BR><BR>
/*!
  Build an Airline object from its attributes.
*/
Airline::Airline(std::string code,std::string name,std::string callsign, std::string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
    flights = 0;
}

/**
 * @brief An operator override function.<BR><BR>
 *
 * Allows airline objects to be compared using the == operator.
 *
 * @param pns : Airline object to be compared.
 * @return \b True if airlines are equivalent, \b false otherwise.
 */
bool Airline::operator==(const Airline &pns) const {
    return code == pns.code;
}