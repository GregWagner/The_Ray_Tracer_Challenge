#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <string>

struct Tuple {
    double x;
    double y;
    double z;
    double w;
    double red;
    double green;
    double blue;
    double alpha;

    Tuple();

    Tuple(double xValue, double yValue, double zValue, double wValue);

    bool isPoint() const;
    bool isVector() const;

    std::string type() const;

    bool operator==(Tuple otherValue) const;

    Tuple operator+(Tuple otherValue) const;

    Tuple operator-(Tuple otherValue) const;

    Tuple operator-() const;

    Tuple operator*(double scalarValue) const;
    Tuple operator*(Tuple otherValue) const;

    Tuple operator/(double scalarValue) const;

    double magnitude() const;
};

Tuple tuple(double xValue, double yValue, double zValue, double wValue);
Tuple point(double xValue, double yValue, double zValue);
Tuple vector(double xValue, double yValue, double zValue);
Tuple color(double redValue, double greenValue, double blueValue);

bool isPoint(Tuple tupleValue);
bool isVector(Tuple tupleValue);

double magnitude(Tuple tupleValue);
Tuple normalize(Tuple tupleValue);

double dot(Tuple tupleValueOne, Tuple tupleValueTwo);

Tuple cross(Tuple tupleValueOne, Tuple tupleValueTwo);
#endif