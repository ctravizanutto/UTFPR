#ifndef GENERICOBJECT_H
#define GENERICOBJECT_H

#include <string>
#include <typeinfo>
#include <QPainter>
#include "matrix.h"

constexpr double PI = 3.14159265358979323846;

enum class CoordType: char {
    world,
    window
};

class GenericObject
{
protected:
    std::unique_ptr<std::string> name = nullptr;

public:
    // interface functions
    virtual void draw(QPainter*) {}
    virtual void transform(Matrix<3, 3>&, CoordType) {}
    virtual void clip() {}

    std::string get_type() { return typeid(this).name(); }
    std::string get_name() { return *name; }
};

#endif // GENERICOBJECT_H
