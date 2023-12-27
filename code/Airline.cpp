//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#include "Airline.h"
//! A constructor.
/*!
  Build an Airline object from its attributes.
*/
Airline::Airline(std::string code,std::string name,std::string callsign, std::string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

bool Airline::operator==(const Airline &pns) const {
    return code == pns.code;
}