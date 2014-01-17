#include "FileProcessor.h"

/*
 * Constructor takes a filename and a mode
 * sets objects fname and fmode to given parameters
 * and opens a file according to the specifications
 * updates the buffer, which is a char array of the file's contents 
 * 
 * default file processing mode is read/write
 */

FileProcessor::FileProcessor(char* name, fileMode mode=rw) {
    fname = name;
    fmode = mode;
    switch(mode) {
        case r:
            file.open(name, std::fstream::in);
            break;
        case w:
            file.open(name, std::fstream::out|std::fstream::app);
            break;
        case rw:
            file.open(name, std::fstream::in|std::fstream::out|std::fstream::app);
            break;
        default:
            file.open(name, std::fstream::in|std::fstream::out|std::fstream::app);
    }
    updateBuffer();
}

/*
 * Essentially a mirror of the constructor in the case 
 * if a file is already open, close it, and let the function open another one
 * 
 * default file processing mode is read/write
 */

void FileProcessor::open(char* name, fileMode mode) {
    if (file.is_open()) {
        file.close();
    }
    fname = name;
    fmode = mode;
    switch(mode) {
        case r:
            file.open(name, std::fstream::in);
            break;
        case w:
            file.open(name, std::fstream::out|std::fstream::app);
            break;
        case rw:
            file.open(name, std::fstream::in|std::fstream::out|std::fstream::app);
            break;
        default:
            file.open(name, std::fstream::in|std::fstream::out|std::fstream::app);
    }
    updateBuffer();
}

/*
 * uhh redundancy
 * 
 * actually this is in there because inheriting 
 * from fstream might be a pain
 * @anirudh if you know how to inherit from fstream
 * and have things not die
 * hmu
 * 
 */ 

void FileProcessor::close() {
    file.close();
}

/*
 * checks if the mode contains w, if not, nothing happens
 * writes current time and a specified val to file
 * updates the buffer
 */ 
void FileProcessor::write(double val) {
    if (!(fmode == w || fmode == rw)) {
        return;
    }
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char output[100];
    char* curtime = asctime (timeinfo); 
    curtime[24] = '\0';
    snprintf(output, 100, "%s: %f", curtime, val);
    file << output << std::endl;
    updateBuffer();
}

/*
 * checks if mode contains r, otherwise does nothing
 * updates the buffer
 * prints certain line of buffer (using clumsy code, will be cleaned up later)
 */ 

void FileProcessor::getline(int ln) {
    if (!(fmode == r || fmode == rw)) {
        return;
    }
    updateBuffer();
    int i = 0;
    int ctr = 0;
    int lineCnt = 1;
    for (int j = 0; j < length; j++) {
        if (buffer[j] == '\n') {
            lineCnt++;
        }
    }
    if (ln > lineCnt) {
        ln = lineCnt-1;
    }
    for (i = 0; i < length; i++) {
        if (buffer[i] == '\n') {
            ctr++;
            if (ctr == ln-1) {
                break;
            }
        }
    }
    i++;
    while (buffer[i] != '\n') {
        printf("%c", buffer[i]);
        i++;
    }
}

/*
 * checks if mode has r, otherwise do nothing
 * reads the file and sets the value 
 * of the char array buffer 
 * to the contents of the file
 */ 

void FileProcessor::updateBuffer() {
    if (!(fmode == r || fmode == rw)) {
        return;
    }
    file.seekg(0, file.end);
    int length_ = file.tellg();
    length = length_;
    file.seekg(0, file.beg);
    
    buffer = NULL;
    buffer = new char[length_];
    file.read(buffer, length_);
}

/*
 * checks if mode has r, otherwise does nothing
 * prints contents of file
 */

void FileProcessor::print() {
    if (!(fmode == r || fmode == rw)) {
        return;
    }
    printf("%s", buffer);
}
