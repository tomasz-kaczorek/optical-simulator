#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtGlobal>

namespace Settings {
    extern qreal minX; //minimum x coordinate of QGraphicsItem
    extern qreal maxX; //maximum x coordinate of QGraphicsItem
    extern qreal minY; //minimum y coordinate of QGraphicsItem
    extern qreal maxY; //maximum y coordinate of QGraphicsItem
    extern qreal minAngle; //minimum rotation of QGraphicsItem
    extern qreal maxAngle; //maximum rotation of QGraphicsItem
    extern qreal minRadius; //minimum radius of Reflector
    extern qreal maxRadius; //maximum radius of Reflector
    extern qreal minFocalLength; //minimum focal length of ConcaveMirror
    extern qreal maxFocalLength; //maximum focal length of ConcaveMirror
    extern qreal minDensity; //minimum density of DiffractionGrating
    extern qreal maxDensity; //maximum density of DiffractionGrating
    extern qreal minBlazingAngle; //minimum blazing angle of DiffractionGrating
    extern qreal maxBlazingAngle; //maximum blazing angle of DiffractionGrating
    extern qreal minWavelength; //minimum LightSource's wavelength
    extern qreal maxWavelength; //maximum LightSource's wavelength
    extern int minQuantity; //minimum quantity of LightSource's rays
    extern int maxQuantity; //maximum quantity of LightSource's rays
    extern qreal screenWidth; //drawing area width
    extern qreal screenHeight; //drawing area height
    extern int decimals; //number of decimals
    extern qreal epsilon; //maximum difference of two qreal values, that are considered equal
    extern unsigned int allowedRecursionDepth; //maximum recursion depth, it determines maximum number of ray's segments
    extern qreal itemPenWidth; //width of the pen used for drawing mirrors
    extern qreal itemNormalLength; //length of the segment denoting the reflective side of mirrors
    extern qreal rayPenWidth;  //width of the pen used for drawing rays
    extern qreal outlineWidth; //width of the interactive area around mirros

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
