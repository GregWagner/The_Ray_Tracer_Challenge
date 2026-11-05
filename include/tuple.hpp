#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <string>

struct Tuple {
    double x;
    double y;
    double z;
    double w;

    Tuple(double xValue, double yValue, double zValue, double wValue);

    bool isPoint();
    bool isVector();

    std::string type();

    bool operator==(Tuple otherValue);

    Tuple operator+(Tuple otherValue);
};

Tuple tuple(double xValue, double yValue, double zValue, double wValue);
Tuple point(double xValue, double yValue, double zValue);
Tuple vector(double xValue, double yValue, double zValue);

bool isPoint(Tuple tupleValue);
bool isVector(Tuple tupleValue);

#endif