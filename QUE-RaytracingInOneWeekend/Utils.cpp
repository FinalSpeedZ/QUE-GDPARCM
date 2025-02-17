#include "Utils.h"

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Function Definitions
double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::random_device rd;
    static std::mt19937 generator(rd());
    return distribution(generator);
}

double random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}
