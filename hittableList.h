#pragma once

#include <memory> // for shared_ptr
#include <vector>

#include "hittable.h"

using std::shared_ptr;

class hittableList
{
private:
    // members
    std::vector< shared_ptr < hittable > > objects;

public:
    // constructors
    hittableList() {}
    hittableList( shared_ptr< hittable > object ) { objects.push_back(object); }

    // methods
    void clear(){ objects.clear(); }
    void add( shared_ptr< hittable > object ) { objects.push_back(object); }
    virtual bool hit( const ray& r, double tMin, double tMax, hitRecord& rec ) const;
};

hittableList randomScene();
hittableList spheres3();