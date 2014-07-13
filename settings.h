#ifndef SETTINGS_H
#define SETTINGS_H

#include <Qt>
#include <QColor>

namespace Settings {
    //variables
    extern qreal minX; //minimum x coordinate of QGraphicsItem
    extern qreal maxX; //maximum x coordinate of QGraphicsItem
    extern qreal minY; //minimum y coordinate of QGraphicsItem
    extern qreal maxY; //maximum y coordinate of QGraphicsItem
    extern QColor primaryColor; //color used for drawing optical devices
    extern QColor secondaryColor; //color used for drawing normal vectors
    extern QColor backgroundColor; //background color of the scene
    extern qreal deviceThickness; //width of the pen used for drawing mirrors
    extern bool normals; //length of the segment denoting the reflective side of mirrors
    extern bool labels;  //width of the pen used for drawing rays
    //constants
    const qreal minAngle = -360.0; //minimum rotation of QGraphicsItem
    const qreal maxAngle = 360.0; //maximum rotation of QGraphicsItem
    const qreal minRadius = 10.0; //minimum radius of Reflector
    const qreal maxRadius = 1000.0; //maximum radius of Reflector
    const qreal minFocalLength = 5.0; //minimum focal length of ConcaveMirror
    const qreal maxFocalLength = 1000.0; //maximum focal length of ConcaveMirror
    const qreal minDensity = 10.0; //minimum density of DiffractionGrating
    const qreal maxDensity = 10000.0; //maximum density of DiffractionGrating
    const qreal minBlazingAngle = -90.0; //minimum blazing angle of DiffractionGrating
    const qreal maxBlazingAngle = 90.0; //maximum blazing angle of DiffractionGrating
    const qreal minWavelength = 380.0; //minimum LightSource's wavelength
    const qreal maxWavelength = 780.0; //maximum LightSource's wavelength
    const int minQuantity = 0; //minimum quantity of LightSource's rays
    const int maxQuantity = 100; //maximum quantity of LightSource's rays
    const int decimals = 6; //number of decimals
    const qreal epsilon = 0.0000001; //maximum difference of two qreal values, that are considered equal
    const unsigned int allowedRecursionDepth = 20; //maximum recursion depth, it determines maximum number of ray's segments
    //functions
    inline bool equalZero(qreal x)
    {
        return fabs(x) < epsilon;
    }

    inline bool lessThanZero(qreal x)
    {
        return (x + epsilon) < 0.0;
    }

    inline bool greaterThanZero(qreal x)
    {
        return (x - epsilon) > 0.0;
    }

    inline bool lessThanOrEqualZero(qreal x)
    {
        return equalZero(x) || lessThanZero(x);
    }

    inline bool greaterThanOrEqualZero(qreal x)
    {
        return equalZero(x) || greaterThanZero(x);
    }

}

#endif // SETTINGS_H
