#include "Interval.h"

#include "Utils.h"

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

// Default constructor
Interval::Interval() : min(+infinity), max(-infinity) {}

// Parameterized constructor
Interval::Interval(double min, double max) : min(min), max(max) {}

// size method
double Interval::size() const {
    return max - min;
}

// contains method
bool Interval::contains(double x) const {
    return min <= x && x <= max;
}

// surrounds method
bool Interval::surrounds(double x) const {
    return min < x && x < max;
}

// clamp method
double Interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
