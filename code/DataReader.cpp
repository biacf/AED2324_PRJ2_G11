//
// Created by AnaBeatrizCarneiroFe on 20/12/2023.
//

#include "DataReader.h"

//! A constructor.
/*!
    Builds a DataReader object from the path of the .csv file to be parsed
*/
DataReader::DataReader(std::string path) {
    filename = std::move(path);
}