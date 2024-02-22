//
// Created by LogiscoolOktatas on 2021. 03. 13..
//

#ifndef UNTITLED_SLIDER_HPP
#define UNTITLED_SLIDER_HPP

#include "Obj.hpp"

class Slider : public Obj {
    int aw{}, ah{};
    Dir d = STOPPED;
public:
    Slider() = default;;

    Slider(int _x, int _y, int _aw, int _ah, int _r, int _g, int _b);

    [[nodiscard]] int get_x() const { return x; }

    [[nodiscard]] int get_y() const { return y; }

    [[nodiscard]] int get_width() const { return aw; }

    [[nodiscard]] int get_height() const { return ah; }

    void draw() const override;

    void set_dir(Dir _d);

    void move(const int &X);

    void reset(int _x, int _y);

    void erase(int _r, int _g, int _b) const;
};

Slider::Slider(int _x, int _y, int _aw, int _ah, int _r, int _g, int _b) {
    x = _x;
    y = _y;
    aw = _aw;
    ah = _ah;
    r = _r;
    g = _g;
    b = _b;
}

void Slider::draw() const {
    genv::gout << genv::move_to(x, y) << genv::color(r, g, b) << genv::box(aw, ah);
}

void Slider::move(const int &X) {
    if (d == LEFT) {
        x -= X / 640;
        x = std::max(x, 0);
    } else if (d == RIGHT) {
        x += X / 640;
        x = std::min(x, X - aw - 1);
    }
}

void Slider::set_dir(Dir _d) {
    d = _d;
}

void Slider::reset(int _x, int _y) {
    x = _x;
    y = _y;
    d = STOPPED;
}

void Slider::erase(int _r, int _g, int _b) const {
    genv::gout << genv::move_to(x, y) << genv::color(_r, _g, _b) << genv::box(aw, ah);
}

#endif //UNTITLED_SLIDER_HPP
