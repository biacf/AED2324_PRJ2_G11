//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#ifndef AED2324_PRJ2_G11_AIRPORT_H
#define AED2324_PRJ2_G11_AIRPORT_H


#include <string>

class Airport {
private:
    std::string code; /*!< Airport code */
    std::string name; /*!< Airport name */
    std::string city; /*!< Airport city */
    std::string country; /*!< Airport country */
    float latitude{}; /*!< Airport latitude */
    float longitude{}; /*!< Airport longitude */
    int incoming;/*!< Incoming Flights */
    int outgoing;/*!< Outgoing Flights */
public:
    Airport()= default;/*! Default constructor */
    Airport(std::string code, std::string name, std::string city, std::string country, float latitude, float longitude);
    /*! A getter method @return Airport code */
    std::string getCode() const{return code;}
    /*! A getter method @return Airport name */
    std::string getName() const{return name;}
    /*! A getter method @return Airport city */
    std::string getCity() const{return city;}
    /*! A getter method @return Airport country */
    std::string getCountry() const{return country;}
    /*! A getter method @return Airport latitude */
    float getLatitude() const{return latitude;}
    /*! A getter method @return Airport longitude */
    float getLongitude() const{return longitude;}
    /*! Increment incoming integer value */
    void incrementIncoming() {incoming++;}
    /*! A getter method @return Incoming flights */
    int getIncoming() const{return incoming;}
    /*! Increment ougoing integer value */
    void incrementOutgoing(){outgoing++;}
    /*! A getter method @return Outgoing flights */
    int getOutgoing() const{return outgoing;}
    /*! @return Number of incoming and outgoing flights */
    int getTraffic() const{return outgoing+incoming;}
};


#endif //AED2324_PRJ2_G11_AIRPORT_H
