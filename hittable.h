#pragma once

#include <memory>

#include "material.h"
#include "ray.h"

struct hitRecord
{
public:
    // members
    point3 point; // hit point
    vec3 normal; // perpendicular from the surface hit point
    std::shared_ptr< material > matPtr;
    double t; // hit time
    bool frontFace;

    // methods
    inline void setFaceNormal( const ray& r, const vec3& outwardNormal )
    {
        // if it's neg, the ray is striking from outside ( front )
        frontFace = dot( r.direction(), outwardNormal ) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable
{
public:
    // methods
    virtual bool hit( const ray& r, double tMin, double tMax, hitRecord& rec ) const = 0;
};