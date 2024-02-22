//
// Created by LogiscoolOktatas on 2021. 03. 13..
//

#ifndef UNTITLED_BRICK_HPP
#define UNTITLED_BRICK_HPP

#include "Obj.hpp"

class Brick : public Obj {
    int w{}, h{};
    bool visible{};
public:
    Brick() = default;

    Brick(int _x, int _y, int _w, int _h, int _r, int _g, int _b, int idx, std::vector<std::vector<short>> &map);

    void draw() const override;

    [[nodiscard]] bool is_visible() const { return visible; };

    void make_visible(std::vector<std::vector<short>> &map, int idx);

    void explode(int _r, int _g, int _b, std::vector<std::vector<short>> &map);
};

Brick::Brick(int _x, int _y, int _w, int _h, int _r, int _g, int _b, int idx,
             std::vector<std::vector<short>> &map) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    r = _r;
    g = _g;
    b = _b;
    visible = true;
    make_visible(map, idx);
}

void Brick::draw() const {
    genv::gout << genv::move_to(x, y) << genv::color(r, g, b) << genv::box_to(x + w - 1, y + h - 1);
}

void Brick::explode(int _r, int _g, int _b, std::vector<std::vector<short>> &map) {
    visible = false;
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            map[i][j] = 0;
        }
    }
    genv::gout << genv::move_to(x, y) << genv::color(_r, _g, _b) << genv::box_to(x + w - 1, y + h - 1);
}

void Brick::make_visible(std::vector<std::vector<short>> &map, int idx) {
    visible = true;
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            map[i][j] = (short) idx;
        }
    }
}

#endif //UNTITLED_BRICK_HPP
