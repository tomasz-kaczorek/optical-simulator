#include <QtGlobal>

namespace Settings {
    qreal minX; //minimum x coordinate of QGraphicsItem
    qreal maxX; //maximum x coordinate of QGraphicsItem
    qreal minY; //minimum y coordinate of QGraphicsItem
    qreal maxY; //maximum y coordinate of QGraphicsItem
    qreal minAngle; //minimum rotation of QGraphicsItem
    qreal maxAngle; //maximum rotation of QGraphicsItem
    qreal minRadius; //minimum radius of Reflector
    qreal maxRadius; //maximum radius of Reflector
    qreal minFocalLength; //minimum focal length of ConcaveMirror
    qreal maxFocalLength; //maximum focal length of ConcaveMirror
    qreal minDensity; //minimum density of DiffractionGrating
    qreal maxDensity; //maximum density of DiffractionGrating
    qreal minBlazingAngle; //minimum blazing angle of DiffractionGrating
    qreal maxBlazingAngle; //maximum blazing angle of DiffractionGrating
    qreal minWavelength; //minimum LightSource's wavelength
    qreal maxWavelength; //maximum LightSource's wavelength
    int minQuantity; //minimum quantity of LightSource's rays
    int maxQuantity; //maximum quantity of LightSource's rays
    qreal screenWidth; //drawing area width
    qreal screenHeight; //drawing area height
    int decimals; //number of decimals
    qreal epsilon; //maximum difference of two qreal values, that are considered equal
    qreal itemPenWidth;
    qreal itemNormalLength;
    qreal rayPenWidth;
    qreal outlineWidth;
}
