#include "hittableList.h"
#include "sphere.h"

// Check everything on the list for a ray hit.
bool hittableList::hit( const ray& r, double tMin, double tMax, hitRecord& rec ) const
{
    hitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = tMax;

    for( const auto& object : objects )
    {
        if( object->hit( r, tMin, closestSoFar, tempRec ) )
        {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}

// Create and return a random scene.
hittableList randomScene()
{
    hittableList world;

    auto groundMaterial = make_shared< lambertian >( color( 0.5, 0.5, 0.5 ) );
    world.add( make_shared< sphere >( point3( 0, -1000, 0 ), 1000, groundMaterial ));

    for( int a = -11; a < 11; a++ )
    {
        for( int b = -11; b < 11; b++ )
        {
            double chooseMat = randomDouble();
            point3 center( a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble() );

            if( ( center - point3( 4, 0.2, 0 ) ).length() > 0.9 )
            {
                shared_ptr< material > sphereMaterial;

                if( chooseMat < 0.8 )
                {
                    // diffuse
                    vec3 albedo = color::random() * color::random();
                    sphereMaterial = make_shared< lambertian >( albedo );
                    world.add( make_shared< sphere >( center, 0.2, sphereMaterial ) );
                }
                else if( chooseMat < 0.95 )
                {
                    // metal
                    vec3 albedo = color::random( 0.5, 1 );
                    double fuzz = randomDouble( 0, 0.5 );
                    sphereMaterial = make_shared< metal >( albedo, fuzz );
                    world.add( make_shared< sphere >( center, 0.2, sphereMaterial ) );
                }
                else
                {
                    // glass
                    sphereMaterial = make_shared< dielectric >( 1.5 );
                    world.add( make_shared< sphere >( center, 0.2, sphereMaterial ) );
                }
            }
        }
    }

    auto material1 = make_shared< dielectric >( 1.5 );
    world.add( make_shared< sphere >( point3( 0, 1, 0 ), 1.0, material1 ) );

    auto material2 = make_shared< lambertian >( color( 0.4, 0.2, 0.1 ) );
    world.add( make_shared< sphere >( point3( -4, 1, 0 ), 1.0, material2 ) );

    auto material3 = make_shared< metal >( color( 0.7, 0.6, 0.5 ), 0.0 );
    world.add( make_shared< sphere >( point3( 4, 1, 0 ), 1.0, material3 ) );

    return world;
}

// Returns a simple 3 sphere scene.
hittableList spheres3()
{
    hittableList world;

    auto materialGround = make_shared< lambertian >( color( 0.8, 0.8, 0.0 ) );
    auto materialCenter = make_shared< lambertian >( color( 0.1, 0.2, 0.5 ) );

    auto materialLeft = make_shared< dielectric >( 1.5 );
    auto materialRight = make_shared< metal >( color( 0.8, 0.6, 0.2 ), 0.0 );

    world.add( make_shared< sphere >( point3( 0.0, -100.5, -1.0 ), 100.0, materialGround ) );
    world.add( make_shared< sphere >( point3( 0.0, 0.0, -1.0 ), 0.5, materialCenter ) );
    world.add( make_shared< sphere >( point3( -1.0, 0.0, -1.0 ), 0.5, materialLeft ) );
    world.add( make_shared< sphere >( point3( 1.0, 0.0, -1.0 ), 0.5, materialRight ) );

    return world;
}