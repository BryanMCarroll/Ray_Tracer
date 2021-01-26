#pragma once

#include "hittable.h"
#include "material.h"

class sphere : public hittable
{
    public:
        // members
        point3 center;
        double radius;
        shared_ptr< material > matPtr;

    public:
        // constructors
        sphere() = delete;
        sphere( point3 cen, double r, shared_ptr< material > mat ) : center( cen ), radius( r ), matPtr( mat ) {};

        // methods
        virtual bool hit( const ray& r, double tMin, double tMax, hitRecord& rec ) const override;
};