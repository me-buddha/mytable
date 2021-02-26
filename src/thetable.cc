#include "thetable.h"
#include <string>

std::string thetable::to_string() {
    std::string str ;
    str += "{" ;
    str += std::to_string(id()) + ",";
    str += name();
    str += "}";
    return str;
}
