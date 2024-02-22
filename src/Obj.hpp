//
// Created by LogiscoolOktatas on 2021. 03. 13..
//

#ifndef UNTITLED_OBJ_HPP
#define UNTITLED_OBJ_HPP

#include <vector>
#include "graphics.hpp"
#include "StatusDir.hpp"

class Obj {
protected:
    int x, y, r, g, b;
public:
    Obj();

    Obj(int _x, int _y, int _r, int _g, int _b) : x(_x), y(_y), r(_r), g(_g), b(_b) {}

    virtual void draw() const = 0;
};

Obj::Obj() {
    x = int();
    y = int();
    r = int();
    g = int();
    b = int();
}

#endif //UNTITLED_OBJ_HPP
