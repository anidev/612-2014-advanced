#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <fstream>
#include <vector>
#include "FileProcessor.h"
#include <Timer.h>

typedef void* obj;
typedef double(*dataFunc)(obj);

struct logger_object {
    obj o;
    dataFunc datafn;
    FileProcessor file;
    double interval;
    Timer timer;
};

class DataLogger {
public:
    DataLogger();
    ~DataLogger();
    void add(logger_object*);
    void update();
private:
    std::vector<logger_object*> loggers;
};

#endif
