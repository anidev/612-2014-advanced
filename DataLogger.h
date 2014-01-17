#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include<fstream>

typedef void* obj;
typedef void(*dataFunc)(obj);


//@anirudh sorry for redundancy
struct logger_object {
    obj o;
    helper h;
};

class DataLogger {
public:
    DataLogger(obj, dataFunc, char*);
    ~DataLogger();
private:
    char* name;
};

#endif
