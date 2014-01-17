#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <fstream>
#include <ctime> 

typedef enum {
    r,
    w,
    rw
} fileMode;

class FileProcessor {
public:
    FileProcessor(char*, fileMode);
    void open(char*, fileMode);
    void close();
    void write(double);
    void getline(int);
    void updateBuffer();
    void print();
private:
    char* fname;
    fileMode fmode;
    std::fstream file;
    char* buffer;
    int length;
};  

#endif
