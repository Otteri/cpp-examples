#include "ExplicitLinking.h"

double Convert::inch2cm(int inches) {
    return(inches * 2.54);
}
double Convert::inch2cm(double inches) {
    return(inches * 2.54);
}

extern "C" __declspec(dllexport)
double Convert_inch2cm(double inches) {
    return Convert::inch2cm(inches);
}