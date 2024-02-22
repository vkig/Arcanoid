//
// Created by vkig on 2021. 03. 13..
//

#ifndef UNTITLED_BUTTON_HPP
#define UNTITLED_BUTTON_HPP

#include <utility>

#include "Obj.hpp"

using namespace genv;

class Button : public Obj {
    int w{}, h{};
    std::string text;
public:
    Button() = default;

    Button(int _x, int _y, int _w, int _h, std::string _text) : w(_w), h(_h), text(std::move(_text)) {
        x = _x;
        y = _y;
        r = 0;
        g = 255;
        b = 255;
    }

    void set_position(int _x, int _y);

    [[nodiscard]] bool mouse_on_it(int ex, int ey) const;

    void draw() const override;

    [[nodiscard]] int get_width() const { return w; }

    [[nodiscard]] int get_height() const { return h; }
};

bool Button::mouse_on_it(int ex, int ey) const {
    if (ex >= x && ex <= x + w && ey >= y && ey <= y + h) {
        return true;
    }
    return false;
}

void Button::draw() const {
    int line_width = 2;
    gout << move_to(x, y) << color(255, 255, 255) << box_to(x + w, y + h)
         << move_to(x + line_width, y + line_width) << color(r, g, b) << box_to(x + w - line_width, y + h - line_width)
         << move_to(x + w / 2 - gout.twidth(text) / 2, y + h / 2 - (gout.cascent() + gout.cdescent()) / 2)
         << genv::move(1, 1)
         << color(0, 0, 0) << genv::text(text) << color(255, 255, 255)
         << move_to(x + w / 2 - gout.twidth(text) / 2, y + h / 2 - (gout.cascent() + gout.cdescent()) / 2)
         << genv::text(text);
}

void Button::set_position(int _x, int _y) {
    x = _x;
    y = _y;
}

#endif //UNTITLED_BUTTON_HPP
