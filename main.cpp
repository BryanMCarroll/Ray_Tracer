#include <iostream>
#include <fstream>

#include "camera.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "hittableList.h"
#include "sphere.h"

int main( int argc, char *argv[] )
{
    if( argc == 1 ){
        std::cout << "Please specify image file path and name as one argument." << std::endl;
        return 1;
    }
    else if( argc > 2 )
    {
        std::cout << "Too many arguments; please specify file path and file name as one argument." << std::endl;
        return 1;
    }

    // Image
    const double aspectRatio = 3.0 / 2.0;
    const int imageWidth = 1200;
    const int imageHeight = static_cast< int >( imageWidth / aspectRatio );
    const int samplesPerPixel = 150;
    const int maxDepth = 50;
    const int totalPixels = imageWidth * imageHeight;
    vec3* image  = new color[totalPixels]; 

    // World
    hittableList world = randomScene();

    // Camera

    point3 lookFrom( 13, 2, 3 );
    point3 lookAt( 0, 0, 0 );
    vec3 vup( 0, 1, 0 );
    double vFov = 20.0;
    double distToFocus = 10.0;
    double aperature = 0.1;

    camera cam( lookFrom, lookAt, vup, vFov, aspectRatio, aperature, distToFocus );

    //Render

    // move down the image
    #pragma omp parallel num_threads(3)
    #pragma omp for
    for( int row = imageHeight - 1; row >= 0; row-- )
    {
        // std::cerr << "\rScanlines remaining: " << row << " " << std::flush;

        // move right across the image
        for( int col = 0; col < imageWidth; col++ )
        {
            color pixelColor( 0, 0, 0 );

            // samples
            for( int s = 0; s < samplesPerPixel; s++ )
            {
                double u = ( col + randomDouble() ) / ( ( ( long int ) imageWidth ) - 1 );
                double v = ( row + randomDouble() ) / ( ( ( long int ) imageHeight ) - 1);
                ray r = cam.getRay( u, v );
                pixelColor += rayColor( r, world, maxDepth );
            } // end samples

            image[imageWidth * row + col] = pixelColor; 

        } // end moving right
    } // end moving down

    // Write to File
    std::ofstream outputFile;
    outputFile.open( argv[1] );
    outputFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for( int row = imageHeight - 1; row >= 0; row-- ){
        for( int col = 0; col < imageWidth; col++ ){
            writeColor( outputFile, image[imageWidth * row + col], samplesPerPixel );
        }
    }

    outputFile.close();
    delete[] image;

    std::cout << "\nDone.\n";

    return 0;
}