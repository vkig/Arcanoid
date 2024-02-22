//
// Created by LogiscoolOktatas on 2021. 03. 13..
//

#ifndef UNTITLED_BALL_HPP
#define UNTITLED_BALL_HPP

#include "Obj.hpp"
#include "Slider.hpp"
#include "Brick.hpp"
#include <random>

class Ball : public Obj {
    int radius{};
    double x{}, y{};
    double v_x{}, v_y{};
    bool visible{};
    bool super_ball{};
    std::vector<std::vector<int>> border;
public:
    Ball() = default;

    Ball(int _x, int _y, int _rad, int _r, int _g, int _b, bool super = false);

    void draw() const override;

    bool move(Slider &slider, std::vector<std::vector<short>> &map, std::vector<Brick> &bricks,
              const std::vector<int> &background,
              Status &status, int &bottom_of_bricks, int &point, const int &X, const int &Y);

    void reset(int _x, int _y);

    void switch_super();

    [[nodiscard]] int getRad() const { return radius; }

    void erase(int _r, int _g, int _b) const;
};

Ball::Ball(int _x, int _y, int _rad, int _r, int _g, int _b, bool super) {
    super_ball = super;
    radius = _rad;
    r = _r;
    g = _g;
    b = _b;
    reset(_x, _y);
    visible = true;
    for (int i = -radius - 1; i < radius + 2; i++) {
        for (int j = -radius - 1; j < radius + 2; j++) {
            if (i * i + j * j > radius * radius && i * i + j * j <= (radius + 1) * (radius + 1)) {
                border.push_back({i, j});
            }
            if (i * i + j * j > (radius + 1) * (radius + 1) && i * i + j * j <= (radius + 2) * (radius + 2) &&
                (((i - 1) * (i - 1) + (j - 1) * (j - 1) <= (radius) * (radius)) ||
                 ((i + 1) * (i + 1) + (j - 1) * (j - 1) <= (radius) * (radius)) ||
                 ((i - 1) * (i - 1) + (j + 1) * (j + 1) <= (radius) * (radius)) ||
                 ((i + 1) * (i + 1) + (j + 1) * (j + 1) <= (radius) * (radius)))) {
                border.push_back({i, j});
            }
        }
    }
}

void Ball::draw() const {
    if (visible) {
        genv::gout << genv::color(r, g, b);
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (i * i + j * j <= radius * radius) {
                    genv::gout << genv::move_to(i + (int) x, j + (int) y) << genv::dot;
                }
            }
        }
    }
    /** To draw border...
    for (auto & a:border)
    {
        genv::gout<<genv::move_to(x+a[0], y+a[1])<<genv::color(255, 0, 0)<<genv::dot;
    }
    */
}

bool Ball::move(Slider &slider, std::vector<std::vector<short>> &map, std::vector<Brick> &bricks,
                const std::vector<int> &background, Status &status,
                int &bottom_of_bricks, int &point, const int &X, const int &Y) {
    std::vector<int> res = {};
    bool collision = false;
    if (x <= radius + 0.5 || x >= X - radius - 1) {
        if (x < radius + 0.5) {
            x = radius + 1;
            v_x = std::abs(v_x);
        }
        if (x > X - radius - 1) {
            x = X - radius - 2;
            v_x = -std::abs(v_x);
        }
    }
    if (y > Y - slider.get_height() - 2 * radius) {
        if (y > Y - radius - 2.1) {
            v_y = 0;
            v_x = 0;
            status = LOSE;
        } else if (y > Y - slider.get_width() - radius - 1 && x >= slider.get_x() - radius &&
                   x < slider.get_x() + slider.get_width() + radius) {
            double deg = atan(((slider.get_y() + slider.get_height()) - y) /
                              std::abs((slider.get_x() + (double) slider.get_width() / 2) - x));
            if (x < slider.get_x() + (double) slider.get_width() / 2)
                deg = M_PI - deg;
            v_y = -sin(deg);
            v_x = cos(deg);
        }
    } else if (y < bottom_of_bricks + 2 * radius) {
        if (y < radius + 0.5) {
            y = radius + 1;
            v_y *= -1;
        }
        if (y > (double) Y / 6 - 2 * radius) {
            for (auto a: border) {
                if (round(x) + a[0] >= 0 && round(x) + a[0] < (int) map.size() && round(y) + a[1] >= 0 &&
                    !map.empty() && round(y) + a[1] < (int) map[0].size() &&
                    map[(int) round(x) + a[0]][(int) round(y) + a[1]] > 0) {
                    bricks[map[(int) round(x) + a[0]][(int) round(y) + a[1]] - 1].explode(background[0], background[1],
                                                                                          background[2], map);
                    if (!collision && !super_ball) {
                        if (abs(a[0]) == radius + 1) {
                            v_x *= -1;
                        } else if (abs(a[1]) == radius + 1) {
                            v_y *= -1;
                        } else {
                            v_x *= -1;
                            v_y *= -1;
                        }
                    }
                    point++;
                    if (point == bricks.size()) {
                        status = WIN;
                    }
                    collision = true;
                }
            }
        }
    }
    x += v_x * X / 640;
    y += v_y * Y / 480;
    return collision;
}

void Ball::reset(int _x, int _y) {
    x = _x;
    y = _y;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(M_PI / 6, M_PI - M_PI / 6);
    double angle = dist(gen);
    v_x = cos(angle);
    v_y = -sin(angle);
}

void Ball::switch_super() {
    super_ball = !super_ball;
}

void Ball::erase(int _r, int _g, int _b) const {
    if (visible) {
        genv::gout << genv::color(_r, _g, _b);
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (i * i + j * j <= radius * radius) {
                    genv::gout << genv::move_to(i + (int) x, j + (int) y) << genv::dot;
                }
            }
        }
    }
}

#endif //UNTITLED_BALL_HPP
