#include<fstream>

class DataLogger {
public:
    typedef void* obj;
    typedef void(*dataFunc)(obj);
    DataLogger(obj, dataFunc, char*);
    ~DataLogger();
private:
    
};
