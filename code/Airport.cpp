//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#include "Airport.h"

//! A constructor.<BR><BR>
/*!
  Build an Airport object from its attributes.
*/
Airport::Airport(std::string code, std::string name, std::string city, std::string country, float latitude, float longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
    incoming = 0;
    outgoing = 0;
}
