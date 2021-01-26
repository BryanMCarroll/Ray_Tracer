#include "vec3.h"

vec3 vec3::random()
{
    return vec3( randomDouble(), randomDouble(), randomDouble() );
}

vec3 vec3::random( double min, double max )
{
    return vec3( randomDouble( min, max ), randomDouble( min, max ), randomDouble( min, max ) );
}

// Use Lambertian Reflection.
// Lambertian Reflection has distribution of cos ( phi ).
vec3 vec3::randomUnitVector()
{
    double a = randomDouble( 0.0, 2.0 * pi );
    double z = randomDouble( -1.0, 1.0 );
    double r = sqrt( 1 - z * z );
    return vec3 ( r * cos( a ), r * sin( a ), z );
}

// Returns the refracted ray.
// unitRay is the incoming/striking ray as a unit vector.
// normal is the surface normal on the side of the incoming ray.
// etaOverEtaP is eta over eta prime.
//     eta is the refractive index of the material that the unitRay is coming from.
//     eta prime is the refractive index of the material that the unitRay is heading into.
//     etaOverEtaP is the eta divided by the eta prime.
//
// Based on Snell's Law: eta * sin( theta ) = etaPrime * sin( thetaPrime )
vec3 refract( const vec3& unitRay, const vec3& normal, double etaOverEtaP )
{
    // first calculate the component of the refracted ray perpendicular to the normal
    double cosTheta = fmin( dot( -unitRay, normal ), 1.0 );
    vec3 rPerp = etaOverEtaP * ( unitRay + cosTheta * normal );

    // now calculate the component of the refracted ray parallel to the normal
    vec3 rParallel = -sqrt( fabs( 1.0 - rPerp.lengthSquared() ) ) * normal;

    // add the component rays to get the refracted ray
    return rPerp + rParallel;
}

// Returns a random vector with a length less than/equal to 1.
vec3 randomInUnitSphere()
{
    while( true )
    {
        vec3 p = vec3::random( -1, 1 );
        if ( p.lengthSquared() >= 1 )
            continue;
        return p;
    }
}
