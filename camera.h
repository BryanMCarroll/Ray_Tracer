#pragma once

#include "rtweekend.h"
#include "vec3.h"
#include "ray.h"

class camera
{
    private:
        // members
        point3 origin;
        point3 lowerLeftCorner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lensRadius;

    public:
        // constructors
        camera( point3 lookFrom, point3 lookAt, vec3 vup, double vfov, double aspectRatio, double aperature, double focusDist );

        // methods
        ray getRay( double s, double t ) const;
};