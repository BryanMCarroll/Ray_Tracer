#include "color.h"

// Returns the final color of the ray taking into account all reflections and refractions.
color rayColor( const ray& rayIn, const hittableList& world, int depth )
{
    ray r = rayIn;
    color acc( 1.0, 1.0, 1.0 ); // accumulation

    for( int i = 0; i < depth + 1; i++ )
    {
        if( i == depth )
        {
            acc *= color( 0.0, 0.0, 0.0);
            break;
        }

        hitRecord rec;
        // ignore hits less than 0.001
        if( world.hit( r, 0.001, infinity, rec ) )
        {
            ray scattered;
            color attenuation;

            if( rec.matPtr->scatter( r, rec, attenuation, scattered ) )
            {
                acc *= attenuation;
                r = scattered;
            }
            else
            {
                return color( 0.0, 0.0, 0.0 );
            }
        }
        else
        {
            break;
        }
    } // end loop

    // Linearly blend the ray color from white at the bottom of the image to blue at the top of the image.
    vec3 unitDirection = unitVector( r.direction() );
    double t = 0.5 * ( unitDirection.y() + 1.0 );
    return acc * ( ( 1.0 - t ) * color( 1.0, 1.0, 1.0 ) + t * color( 0.5, 0.7, 1.0 ) ) ;
}

void writeColor( std::ostream& out, color pixelColor, int samplesPerPixel )
{

    double scale = 1.0 / ( double ) samplesPerPixel;
    // "use "gamma 2", which means raising to the power 1/gamma, or in
    // our simple case 1/2, which is square root."
    double r = sqrt( scale * pixelColor.x() );
    double g = sqrt( scale * pixelColor.y() );
    double b = sqrt( scale * pixelColor.z() );

    // Write the translated [0,255] value of each color component
    out << static_cast< int >( 256 * clamp( r, 0.0, 0.999 ) ) << ' '
        << static_cast< int >( 256 * clamp( g, 0.0, 0.999 ) ) << ' '
        << static_cast< int >( 256 * clamp( b, 0.0, 0.999 ) ) << '\n';
}