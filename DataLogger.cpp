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
        logger_object* cur = loggers.at(i);
        if (cur->timer.Get() >= cur->interval) {
            cur->file.write(((cur->datafn)(cur->o)));
            cur->timer.Reset();
        }
    }
}
