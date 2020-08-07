#include "diffractiongrating.h"

#include "label.h"
#include "opticalsystem.h"
#include "ray.h"
#include "settings.h"

#include <qmath.h>
#include <QPainter>

DiffractionGrating::DiffractionGrating(QString name, qreal x, qreal y, qreal angle, qreal radius, qreal blazeAngle, qreal density, OpticalSystem * opticalSystem, QGraphicsItem * parent) :
    Reflector(opticalSystem, parent),
    m_radius(radius),
    m_blazeAngle(blazeAngle),
    m_density(density)
{
    prepareGeometryChange();
    addLabel();
    addNormal();
    setName(name);
    setX(x);
    setY(y);
    setRotation(angle);
    m_pen.setStyle(Qt::DotLine);
    build();
}

DiffractionGrating::~DiffractionGrating()
{
    foreach(Ray * ray, m_rays) ray->plot();
}

qreal DiffractionGrating::radius()  const
{
    return m_radius;
}

void DiffractionGrating::setRadius(qreal radius)
{
    m_radius = radius;
}

qreal DiffractionGrating::blazeAngle() const
{
    return m_blazeAngle;
}

void DiffractionGrating::setBlazeAngle(qreal blazeAngle)
{
    m_blazeAngle = blazeAngle;
}

qreal DiffractionGrating::density() const
{
    return m_density;
}

void DiffractionGrating::setDensity(qreal density)
{
    m_density = density;
}
#include <QDebug>
void DiffractionGrating::build(bool blaze, bool density)
{
    prepareGeometryChange();
    Orders orders;
    if(blaze)
    {
        m_blazeHead = QPointF(qCos(((m_blazeAngle + rotation()) * M_PI / 180.0)), qSin((m_blazeAngle + rotation()) * M_PI / 180.0));
        orders |= Orders::Max;
    }
    if(density)
    {
        orders |= Orders::SecondNegative | Orders::FirstNegative | Orders::FirstPositive | Orders::SecondPositive;
    }
    if(blaze || density)
    {
        m_rays.append(nullptr);
        while(Ray * ray = m_rays.takeFirst())
        {
            ray->replot(orders);
            m_rays.append(ray);
        }
    }
    else
    {
        m_path = QPainterPath(QPointF(0.0, -m_radius));
        m_path.lineTo(QPointF(0.0, m_radius));
        m_leftEdge = leftEdge();
        m_rightEdge = rightEdge();
        m_blazeHead = QPointF(qCos(((m_blazeAngle + rotation()) * M_PI / 180.0)), qSin((m_blazeAngle + rotation()) * M_PI / 180.0));
        m_rays.append(nullptr);
        while(Ray * ray = m_rays.takeFirst()) ray->plot();
        foreach(LightSource * lightSource, m_opticalSystem->lightSources()) lightSource->replot(this);
    }
}

QPointF DiffractionGrating::leftEdge() const
{
    return mapToScene(QPointF(0.0, -m_radius));
}

QPointF DiffractionGrating::rightEdge() const
{
    return mapToScene(QPointF(0.0, m_radius));
}

qreal DiffractionGrating::scalar(Ray const * ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the diffraction grating's edges lie
    qreal l = rdy * (m_leftEdge.x() - rx) - rdx * (m_leftEdge.y() - ry);
    qreal r = rdy * (m_rightEdge.x() - rx) - rdx * (m_rightEdge.y() - ry);
    //both points lie on the same side of ray - intersection impossible
    if((Settings::fuzzyIsGreaterThanZero(l) && Settings::fuzzyIsGreaterThanZero(r)) || (Settings::fuzzyIsLessThanZero(l) && Settings::fuzzyIsLessThanZero(r))) return -1.0;
    qreal gx = m_leftEdge.x(); //x coordinate of diffraction grating segment edge
    qreal gy = m_leftEdge.y(); //y coordinate of diffraction grating segment edge
    qreal gdx = m_rightEdge.x() - gx; //horizontal component of the diffraction grating segment's vector
    qreal gdy = m_rightEdge.y() - gy; //vertical component of the diffraction grating segment's vector
    //plugging (x = rx + d * rdx) and (y = ry + d * rdy) into line equation (gdy * (x - gx) - gdx * (y - gy) = 0) and solving for d
    return (gdx * ry - gdy * rx + gdy * gx - gdx * gy) / (gdy * rdx - gdx * rdy);
}

void DiffractionGrating::reflect(Ray * ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal gx = vector.x2(); //x coordinate of ray-diffraction grating intersection point
    qreal gy = vector.y2(); //y coordinate of ray-diffraction grating intersection point
    qreal gdx = m_leftEdge.x() - m_rightEdge.x(); //horizontal component of the line between diffraction grating's edges
    qreal gdy = m_leftEdge.y() - m_rightEdge.y(); //vertical component of the line between diffraction grating's edges
    //calculate on which side of a diffraction grating does the ray begin
    //if it begins on the back side, return as there will be no reflection
    if(Settings::fuzzyIsGreaterThanOrEqualToZero(gdy * (rx - gx) - gdx * (ry - gy))) return;
    //find a vector (gdx, gdy) perpedicular to diffraction grating surface
    gdx = m_rightEdge.y() - m_leftEdge.y();
    gdy = m_leftEdge.x() - m_rightEdge.x();
    //plug: (x = gx + d * gdx) and (y = gy + d * gdy) into distance equation between (rx, ry) and (x, y): sqrt((x - rx) ^ 2 + (y - ry) ^ 2)
    //abandon the root (as it is irrelevant) and minimize result to find projection of (rx, ry) on line perpedicular to diffraction grating's surface
    //parabola's tip is located at d = -b / 2 * a
    qreal d = (gdx * (rx - gx) + gdy * (ry - gy)) / (gdx * gdx + gdy * gdy);
    qreal nx = gx + d * gdx; //x coordinate of (rx, ry) projection on normal
    qreal ny = gy + d * gdy; //y coordinate of (rx, ry) projection on normal
    if(ray->order(Orders::Zero))
    {
        ray->append(2.0 * nx - rx, 2.0 * ny - ry, Orders::Zero);
    }
    //calculate sine of the incident angle, it is equal to distance from (nx, ny) to (rx, ry) divided by distance from (rx, ry) to (gx, gy)
    qreal L = qSqrt((nx - rx) * (nx - rx) + (ny - ry) * (ny - ry)); //length of the ((rx, ry), (nx, ny)) vector
    qreal R = qSqrt((gx - rx) * (gx - rx) + (gy - ry) * (gy - ry)); //length of the ((rx, ry), (gx, gy)) vector (incident ray)
    qreal h = qSqrt((nx - gx) * (nx - gx) + (ny - gy) * (ny - gy)); //length of the ((gx, gy), (nx, ny)) vector
    qreal c = ray->wavelength() * density() * 1.0e-6; //order coefficient
    if(ray->order(Orders::SecondNegative))
    {
        d = -2.0 * c - L / R;
        if(d < 1.0 && d > -1.0)
        {
            d = h * d / qSqrt(1 - d * d);
            d = 1 - d / L;
            ray->append(rx + d * (nx - rx), ry + d * (ny - ry), Orders::SecondNegative);
        }
    }
    if(ray->order(Orders::FirstNegative))
    {
        d = -1.0 * c - L / R;
        if(d < 1.0 && d > -1.0)
        {
            d = h * d / qSqrt(1 - d * d);
            d = 1 - d / L;
            ray->append(rx + d * (nx - rx), ry + d * (ny - ry), Orders::FirstNegative);
        }
    }
    if(ray->order(Orders::FirstPositive))
    {
        d = 1.0 * c - L / R;
        if(d < 1.0 && d > -1.0)
        {
            d = h * d / qSqrt(1 - d * d);
            d = 1 - d / L;
            ray->append(rx + d * (nx - rx), ry + d * (ny - ry), Orders::FirstPositive);
        }
    }
    if(ray->order(Orders::SecondPositive))
    {
        d = 2.0 * c - L / R;
        if(d < 1.0 && d > -1.0)
        {
            d = h * d / qSqrt(1 - d * d);
            d = 1 - d / L;
            ray->append(rx + d * (nx - rx), ry + d * (ny - ry), Orders::SecondPositive);
        }
    }
    if(ray->order(Orders::Max))
    {
        gdx = m_blazeHead.x();
        gdy = m_blazeHead.y();
        d = (gdx * (rx - gx) + gdy * (ry - gy)) / (gdx * gdx + gdy * gdy);
        nx = gx + d * gdx;
        ny = gy + d * gdy;
        gdx = m_leftEdge.x() - m_rightEdge.x();
        gdy = m_leftEdge.y() - m_rightEdge.y();
        if(Settings::fuzzyIsGreaterThanOrEqualToZero(gdy * (2.0 * nx - gx) - gdx * (2.0 * ny - gy))) return;
        ray->append(2.0 * nx - rx, 2.0 * ny - ry, Orders::Max);
    }
}

int DiffractionGrating::type() const
{
    return OpticalDevice::DiffractionGrating;
}

