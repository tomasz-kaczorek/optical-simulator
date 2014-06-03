#include "reflector.h"

Reflector::Reflector(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    setFlag(ItemSendsGeometryChanges, true);
}

Reflector::~Reflector()
{
}

