#include "rtweekend.h"

double degreesToRadians( double degrees )
{
    return degrees * pi / 180.0;
}

double randomDouble()
{
    // Returns a random real in [0,1);
    // return rand() / ( RAND_MAX + 1.0 );

    static std::uniform_real_distribution< double > distribution( 0.0, 1.0 );
    static std::mt19937 generator;
    return distribution( generator );
}

double randomDouble( double min, double max )
{
    // Returns a random real in [min, max)
    return min + ( max - min ) * randomDouble();
}

double clamp( double x, double min, double max )
{
    if ( x < min ) return min;
    if ( x > max ) return max;
    return x;
}