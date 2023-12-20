//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#ifndef AED2324_PRJ2_G11_DATAREADER_H
#define AED2324_PRJ2_G11_DATAREADER_H


#include <string>
#include <fstream>

class DataReader {
private:
    std::string filename; /*!< Path to the .csv file*/
    std::ifstream file; /*!< ifstream object */
public:
    //constructor
    explicit DataReader(std::string path);
    //methods
};


#endif //AED2324_PRJ2_G11_DATAREADER_H
