#include "material.h"
#include "hittable.h"
#include "vec3.h"

bool metal::scatter( const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered ) const
{
    vec3 reflected = reflect( unitVector( rIn.direction()), rec.normal );
    scattered = ray( rec.point, reflected + fuzz * randomInUnitSphere() );
    attenuation = albedo;
    return ( dot( scattered.direction(), rec.normal ) ) > 0;
}

bool lambertian::scatter( const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered ) const
{
    vec3 scatterDirection = rec.normal + vec3::randomUnitVector();
    scattered = ray( rec.point, scatterDirection );
    attenuation = albedo;
    return true;
}

bool dielectric::scatter( const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered ) const
{
    attenuation = color( 1.0, 1.0, 1.0 ); // no attenuation

    // Calculate the refraction ratio ( eta / etaPrime ).
     // The refractive index of air is 1.0.
    double etaOverEtaP = rec.frontFace ? ( 1.0 / refractIdx ) : refractIdx;

    vec3 unitDirection = unitVector( rIn.direction() );

    // Calculate the cos( theta ) and sin( theta ) between the normal of the surface and the incoming ray.
    double cosTheta = fmin( dot( -unitDirection, rec.normal ), 1.0 );
    double sinTheta = sqrt( 1.0 - cosTheta * cosTheta );

    if( etaOverEtaP * sinTheta > 1.0 )
    {
        // No solution. So, the ray must reflect.
        vec3 reflected = reflect( unitDirection, rec.normal );
        scattered = ray( rec.point, reflected );
    }
    else
    {
        double reflectProb = schlick( cosTheta, etaOverEtaP );
        if( randomDouble() < reflectProb )
        {
            // reflect
            vec3 reflected = reflect( unitDirection, rec.normal );
            scattered = ray ( rec.point, reflected );
        }
        else
        {
            // refract
            vec3 refracted = refract( unitDirection, rec.normal, etaOverEtaP );
            scattered = ray( rec.point, refracted );
        }
    }

    return true;
}

// Schlick Approximation
// Glass has a reflectivity that varies with angle.
double schlick( double cosine, double refractIdx )
{
    double r0 = ( 1 - refractIdx ) / ( 1 + refractIdx );
    r0 = r0 * r0;
    return r0 + ( 1 - r0 ) * pow( ( 1 - cosine ), 5 );
}
