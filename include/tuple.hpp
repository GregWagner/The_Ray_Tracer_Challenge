#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <string>

struct Tuple {
    double x;
    double y;
    double z;
    double w;

    Tuple(double x_value, double y_value, double z_value, double w_value);

    bool is_point();
    bool is_vector();

    std::string type();

    bool operator==(Tuple other);

    Tuple operator+(Tuple other);
};

Tuple tuple(double x, double y, double z, double w);
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);

bool is_point(Tuple t);
bool is_vector(Tuple t);

#endif