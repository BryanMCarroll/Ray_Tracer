#pragma once

// std includes
#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits< double >::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

double degreesToRadians( double degrees );
double randomDouble();
double randomDouble( double min, double max );
double clamp( double x, double min, double max );