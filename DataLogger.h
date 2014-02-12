#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <fstream>
#include <vector>
#include "FileProcessor.h"

typedef void* obj;
typedef char* (*dataFunc)(obj);

struct logger_object {
    obj o;
    dataFunc datafn;
    FileProcessor file;
    double interval;
    double ctr;
};

class DataLogger {
public:
    DataLogger();
    ~DataLogger();
    void add(obj, dataFunc, FileProcessor, double, double);
    void update();
private:
    std::vector<logger_object*> loggers;
};

#endif
