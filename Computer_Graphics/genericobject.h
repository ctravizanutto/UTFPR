#ifndef GENERICOBJECT_H
#define GENERICOBJECT_H

#include <string>
#include <typeinfo>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <matrix.h>
#include <cmath>

class GenericObject
{
    std::string name;
    std::string type;

public:
    GenericObject(const std::string& name) { this->name = name; }
    virtual ~GenericObject() {}
    virtual void draw(QPainter*) {}
    std::string get_name() { return this->name; }
    virtual std::string get_type() { return typeid(this).name(); }
    virtual void rotate(double) {}
    virtual void translation(double, double) {}
    virtual void rescale(double, double) {}

};

#endif // GENERICOBJECT_H
