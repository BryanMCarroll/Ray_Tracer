#include "camera.h"

camera::camera( point3 lookFrom, point3 lookAt, vec3 vup, double vfov, double aspectRatio, double aperature, double focusDist )
{
    double theta = degreesToRadians( vfov );
    double h = tan( theta / 2 );
    double viewportHeight = 2.0 * h;
    double viewportWidth = aspectRatio * viewportHeight;

    w = unitVector( lookFrom - lookAt );
    u = unitVector( cross( vup, w ) );
    v = cross( w, u );

    origin = lookFrom;
    horizontal = focusDist * viewportWidth * u;
    vertical = focusDist * viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDist * w;
    lensRadius = aperature / 2;
}

ray camera::getRay( double s, double t ) const
{
    vec3 rd = lensRadius * randomInUnitSphere();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray( origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset );
}