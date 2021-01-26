#pragma once

#include "rtweekend.h"
#include "ray.h"

class material
{
public:
    // methods
    virtual bool scatter( const ray& rIn, const struct hitRecord& rec, color& attenuation, ray& scattered ) const = 0;
};

class metal : public material
{
public:
    // members
    color albedo;
    double fuzz;

    // constructors
    metal( const color& a, double f  ) : albedo( a ), fuzz( f < 1 ? f : 1 ) {};

    // methods
    virtual bool scatter( const ray& rIn, const struct hitRecord& rec, color& attenuation, ray& scattered ) const override;
};

class lambertian : public material
{
public:
    // members
    color albedo;

public:
    // constructors
    lambertian( const color& a ) : albedo( a ) {};

    // methods
    virtual bool scatter( const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered ) const override;
};

class dielectric : public material
{
public:
    // members
    double refractIdx; // refraction index

    // constructors
    dielectric( double ri ) : refractIdx( ri ) {}

    // methods
    virtual bool scatter( const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered ) const override;
};

double schlick( double cosine, double refIdx );