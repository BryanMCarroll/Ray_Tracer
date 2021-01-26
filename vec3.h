#pragma once

#include < cmath >
#include < iostream >

#include "rtweekend.h"

class vec3
{    
    public:
        // members
        double e[3];

        // constructors
        vec3() : e{ 0.0, 0.0, 0.0 } {}
        vec3( double e0, double e1, double e2 ) : e{ e0, e1, e2 } {}

        // methods
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator - () const { return vec3 ( -e[0], -e[1], -e[2] ); }
        double operator [] ( int i ) const { return e[i]; }
        // double& operator [] ( int i ) const {return e[ i ]; }

        vec3& operator = ( const vec3& v )
        {
            e[0] = v.e[0];
            e[1] = v.e[1];
            e[2] = v.e[2];
            return *this;
        }

        vec3& operator += ( const vec3& v )
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator *= ( const double t )
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator /= ( const double t )
        {
            return *this *= 1 / t;
        }

        vec3& operator *= ( const vec3& v )
        {
            e[0] *= v.e[0];
            e[1] *= v.e[1];
            e[2] *= v.e[2];
            return *this;
        }

        double length() const
        {
            return sqrt( lengthSquared() );
        }

        double lengthSquared() const
        {
            return e[0] * e[0] + e[1] * e[1] + e [2] * e[2];
        }

        static vec3 random();
        static vec3 random( double min, double max );
        static vec3 randomUnitVector ();
};

// aliases for clarity
using point3 = vec3;
using color = vec3;

inline std::ostream& operator << ( std::ostream& out, const vec3& v )
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator + ( const vec3& u, const vec3& v )
{
    return vec3( u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2] );
}

inline vec3 operator - ( const vec3& u, const vec3& v )
{
    return vec3( u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2] );
}

inline vec3 operator * ( const vec3& u, const vec3& v )
{
    return vec3( u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2] );
}

inline vec3 operator * ( double t, const vec3& v )
{
    return vec3( t * v.e[0], t * v.e[1], t * v.e[2] );
}

inline vec3 operator * ( const vec3& v, double t )
{
    return t * v;
}

inline vec3 operator / ( const vec3& v, double t )
{
    return ( 1 / t ) * v;
}

inline double dot( const vec3& u, const vec3& v )
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross( const vec3& u, const vec3& v )
{
    return vec3( u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0] );
}

inline vec3 unitVector( const vec3& v )
{
    return v / v.length();
}

inline vec3 reflect( const vec3& v, const vec3& n )
{
    return  v - 2 * dot( v, n ) * n;
}

vec3 randomInUnitSphere();
vec3 refract( const vec3& uv, const vec3& n, double etaiOverEtat );