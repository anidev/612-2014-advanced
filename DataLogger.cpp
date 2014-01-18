#include "DataLogger.h"

DataLogger::DataLogger() {
    
}

DataLogger::~DataLogger() {
    
}

void DataLogger::add(logger_object* lo) {
    loggers.push_back(lo);
}

void DataLogger::update() {
    for (int i = 0; i < (int)loggers.size(); i++) {
        loggers.at(i) -> file.write(((loggers.at(i) -> datafn)(loggers.at(i) -> o)));
    }
}
