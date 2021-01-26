#include "sphere.h"

// Returns true if the sphere is hit by the ray r.
// Returns false if there is no hit.
// The hitRecord will be filled if there is a hit.
bool sphere::hit( const ray& r, double tMin, double tMax, hitRecord& rec ) const
{
    vec3 oc = r.origin() - center;

    // Use a simplified version of the quadratic formula
    // by setting b = 2h.
    double a = r.direction().lengthSquared();
    double halfb = dot( oc, r.direction() );
    double c = oc.lengthSquared() - radius * radius;

    double discriminant = halfb * halfb - a * c;

    // A negative discriminant is no hits.
    // Discrimant = 0 is 1 hit.
    // A Positive discriminant is two hits.

    if( discriminant > 0.0 ) // = 0.0 is very unlikely.
    {
        double root = sqrt( discriminant );

        double t = ( -halfb - root ) / a;
        if( tMin < t && t < tMax ) // between tMin and tMax
        {
            rec.t = t;
        }
        else
        {
            t = ( -halfb + root ) / a;
            if ( tMin < t && t < tMax ) // between tMin and tMax
            {
                rec.t = t;
            }
            else
            {
                return false;
            }
        }

        rec.point = r.at( rec.t );
        // The normal is perpendicular to the surface hit point P.
        vec3 outwardNormal = ( rec.point - center ) / radius;
        rec.setFaceNormal( r, outwardNormal );
        rec.matPtr = matPtr;
        return true;
    } // end ( discriminant > 0.0 )

    return false;
} // end sphere::hit