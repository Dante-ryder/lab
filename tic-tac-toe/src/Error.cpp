#include <Error.h>
#include <string>
#include <iostream>

using namespace std;

Error::Error() {}

void Error::throw_error(string error_msg) {
   cerr << error_msg << endl;
}

Error::~Error() {}