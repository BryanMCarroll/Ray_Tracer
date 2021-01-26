#pragma once

#include "vec3.h"
#include "ray.h"
#include "hittableList.h"

void writeColor( std::ostream& out, color pixelColor, int samplesPerPixel );
color rayColor( const ray& rayIn, const hittableList& world, int depth );
void writeColor( std::ostream& out, color pixelColor, int samplesPerPixel );