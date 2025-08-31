#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

class Error
{
private:
    /* data */
public:
    Error(/* args */);
    void throw_error(string error_msg);
    ~Error();
};


#endif