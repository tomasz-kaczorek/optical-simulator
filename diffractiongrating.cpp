#include "diffractiongrating.h"

#include "label.h"
#include "ray.h"
#include "settings.h"

#include <QPainter>

DiffractionGrating::DiffractionGrating(QGraphicsItem *parent) :
    Reflector(parent),
    m_radius(0.0),
    m_blazingAngle(0.0),
    m_density(0.0)
{
    setFlag(ItemSendsGeometryChanges, true);
}

DiffractionGrating::~DiffractionGrating()
{
}

qreal DiffractionGrating::radius()  const
{
    return m_radius;
}

void DiffractionGrating::setRadius(qreal radius)
{
    if(m_radius == radius) return;
    prepareGeometryChange();
    m_radius = radius;
}

qreal DiffractionGrating::blazingAngle() const
{
    return m_blazingAngle;
}

void DiffractionGrating::setBlazingAngle(qreal blazingAngle)
{
    m_blazingAngle = blazingAngle;
}

qreal DiffractionGrating::density() const
{
    return m_density;
}

void DiffractionGrating::setDensity(qreal density)
{
    m_density = density;
}

QPointF DiffractionGrating::leftEdge() const
{
    return mapToScene(QPointF(0.0, -m_radius));
}

QPointF DiffractionGrating::rightEdge() const
{
    return mapToScene(QPointF(0.0, m_radius));
}

void DiffractionGrating::geometryChanged()
{
    m_left = leftEdge();
    m_right = rightEdge();
    m_label->geometryChanged();
}

qreal DiffractionGrating::intersectionDistance(Ray const *ray) const
{
    QLineF vector = ray->line();
    qreal rx = vector.x1(); //x coordinate of ray starting point
    qreal ry = vector.y1(); //y coordinate of ray starting point
    qreal rdx = vector.dx(); //horizontal component of the ray's vector
    qreal rdy = vector.dy(); //vertical component of the ray's vector
    //calculate on which side of a ray do the diffraction grating's edges lie
    qreal l = rdy * (m_left.x() - rx) - rdx * (m_left.y() - ry);
    qreal r = rdy * (m_right.x() - rx) - rdx * (m_right.y() - ry);
    //both points lie on the same side of ray - intersection impossible
    if((Settings::greaterThanZero(l) && Settings::greaterThanZero(r)) || (Settings::lessThanZero(l) && Settings::lessThanZero(r))) return -1.0;
    qreal gx = m_left.x(); //x coordinate of mirror segment edge
    qreal gy = m_left.y(); //y coordinate of mirror segment edge
    qreal gdx = m_right.x() - gx; //horizontal component of the mirror segment's vector
    qreal gdy = m_right.y() - gy; //vertical component of the mirror segment's vector
    //plugging (x = rx + d * rdx) and (y = ry + d * rdy) into line equation (gdy * (x - gx) - gdx * (y - gy) = 0) and solving for d
    return (gdx * ry - gdy * rx + gdy * gx - gdx * gy) / (gdy * rdx - gdx * rdy);
}

void DiffractionGrating::reflectionVector(Ray *ray, bool *orders) const
{

}

QRectF DiffractionGrating::boundingRect() const
{
    return QRectF(-Settings::itemPenWidth / 2.0, -m_radius - Settings::itemPenWidth / 2.0, Settings::itemNormalLength + Settings::itemPenWidth, 2.0 * m_radius + Settings::itemPenWidth);
}

QPainterPath DiffractionGrating::shape() const
{
    QPainterPath path;
    path.moveTo(0.0, -m_radius);
    path.lineTo(0.0, m_radius);
    QPainterPathStroker stroker;
    stroker.setCapStyle(Qt::RoundCap);
    stroker.setJoinStyle(Qt::RoundJoin);
    stroker.setWidth(Settings::outlineWidth);
    return stroker.createStroke(path);
}

void DiffractionGrating::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QColor(Qt::gray), 0.0));
    painter->drawLine(0.0, 0.0, Settings::itemNormalLength, 0.0);
    painter->setPen(QPen(QColor(Qt::black), Settings::itemPenWidth, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0.0, -m_radius, 0.0, m_radius);
    painter->setPen(QPen(QColor(Qt::black), Settings::itemPenWidth, Qt::DotLine, Qt::RoundCap));
    painter->drawLine(1.0, -m_radius, 1.0, m_radius);
}
