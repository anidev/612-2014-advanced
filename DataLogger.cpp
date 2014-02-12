#include "DataLogger.h"

DataLogger::DataLogger() {
    
}

DataLogger::~DataLogger() {
    
}

void DataLogger::add(obj o, dataFunc df, FileProcessor fp, double interval, double ctr) {
    logger_object* lo;
    lo->o = o;
    lo->datafn = df;
    lo->file = fp;
    lo->interval = interval;
    lo->ctr = ctr;
    loggers.push_back(lo);
}

void DataLogger::update() {
    for (int i = 0; i < (int)loggers.size(); i++) {
        logger_object* cur = loggers.at(i);
        if (cur->ctr > cur->interval) {
            cur->file.write(((cur->datafn)(cur->o)));
            cur->ctr = 0;
        } else {
            cur->ctr++;
        }
    }
}
