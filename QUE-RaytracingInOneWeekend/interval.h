#ifndef INTERVAL_H
#define INTERVAL_H

class Interval
{
public:
    double min, max;

    Interval(); // Default constructor declaration
    Interval(double min, double max); // Parameterized constructor declaration

    double size() const; // size method declaration
    bool contains(double x) const; // contains method declaration
    bool surrounds(double x) const; // surrounds method declaration
    double clamp(double x) const; // clamp method declaration

    static const Interval empty, universe; // Static constants declaration
};

#endif
