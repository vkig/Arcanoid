//
// Created by vkig on 2021. 03. 09..
//
#ifndef UNTITLED_BRICKBREAKER_HPP
#define UNTITLED_BRICKBREAKER_HPP

#include <iostream>
#include "Ball.hpp"
#include "Brick.hpp"
#include "Slider.hpp"
#include "Button.hpp"
#include "Picture.hpp"

class BrickBreaker {
    const std::vector<std::vector<int>> colors = {
            {157, 157, 151},
            {255, 21,  2},
            {255, 242, 0},
            {0,   109, 253},
            {255, 41,  255},
            {0,   214, 3}
    };
    const std::vector<int> background = {0, 5, 100};
    const int X;
    const int Y;
    std::vector<std::vector<short>> map;
    Picture menu;
    Picture win;
    Picture game_over;
    Status status = MENU;
    Ball ball;
    Slider slider;
    Button newGame;
    unsigned frame_counter = 0;
    std::vector<Brick> bricks;
    bool right{};
    bool left{};
    bool collision = true;
    int point{};
    int bottom_of_bricks{};

    void draw_all(bool init = false);

    void draw_menu();

    void draw_lose();

    void draw_win();

public:
    BrickBreaker();

    BrickBreaker(const int &XX, const int &YY);


    void event_manager(genv::event &ev);
};

BrickBreaker::BrickBreaker() : X(400), Y(400) {
    ball = Ball();
    slider = Slider();
}

BrickBreaker::BrickBreaker(const int &XX, const int &YY) : X(XX), Y(YY) {
    menu = Picture("pic.kep");
    win = Picture("win.kep", true, 150, 150, 150);
    game_over = Picture("game_over.kep", true, 50, 50, 50);
    int width = X / 10;
    int height = Y / 48;
    slider = Slider(X / 2 - width / 2, Y - height - 1, width, height, 125, 125, 125);
    int rad = X / 128;
    ball = Ball(X / 2, Y - slider.get_height() - 2 * rad, rad, 255, 255, 255);
    map = std::vector<std::vector<short>>(X, std::vector<short>(Y, 0));
    int bricks_in_a_row = 20;
    for (int i = 0; i < colors.size(); i++) {
        for (int j = 0; j < bricks_in_a_row; j++) {
            bricks.push_back(
                    Brick(j * X / 20 + 1, Y / 6 + i * Y / 40, X / 20 - 2, Y / 40 - 2, colors[i][0],
                          colors[i][1], colors[i][2], i * bricks_in_a_row + j + 1, map));
        }
    }
    bottom_of_bricks = Y / 6 + Y / 40 * (int) colors.size() - 2;
    right = false;
    left = false;
    point = 0;
    int b_width = 250;
    int b_height = 50;
    newGame = Button(X / 2 - b_width / 2, Y / 2 + menu.height() * 3 / 4 - b_height / 2, b_width, b_height, "New Game");
    status = MENU;
}


void BrickBreaker::event_manager(genv::event &ev) {
    if (status == PLAYING) {
        if (ev.type == genv::ev_key) {
            if (ev.keycode == 80 || ev.keycode == 'a') {
                left = true;
            } else if (ev.keycode == 79 || ev.keycode == 'd') {
                right = true;
            } else if (ev.keycode == -80 || ev.keycode == -'a') {
                left = false;
            } else if (ev.keycode == -79 || ev.keycode == -'d') {
                right = false;
            }
            if (right && !left) {
                slider.set_dir(RIGHT);
            } else if (left && !right) {
                slider.set_dir(LEFT);
            } else {
                slider.set_dir(STOPPED);
            }
            if (ev.keycode == 'u') {
                ball.switch_super();
            }
        }
        if (ev.type == genv::ev_timer) {
            ball.erase(background[0], background[1], background[2]);
            slider.erase(background[0], background[1], background[2]);
            collision = ball.move(slider, map, bricks, background, status, bottom_of_bricks, point, X, Y);
            slider.move(X);
            draw_all();
        }
    } else if (status == MENU) {
        if (ev.type == genv::ev_timer) {
            draw_menu();
        }
    } else if (status == MENUDRIWEN) {
        genv::gout.showmouse(true);
        if (ev.type == genv::ev_mouse || (ev.type == genv::ev_key && ev.keycode == key_space)) {
            if (ev.button == genv::btn_left || ev.keycode == key_space) {
                if (newGame.mouse_on_it(ev.pos_x, ev.pos_y) || ev.keycode == key_space) {
                    status = PLAYING;
                    ball.reset(X / 2, Y - slider.get_height() - 2 * ball.getRad());
                    int width = 101;
                    right = false;
                    left = false;
                    slider.reset(X / 2 - width / 2, Y - slider.get_height() - 1);
                    for (int i = 0; i < bricks.size(); i++) {
                        bricks[i].make_visible(map, i + 1);
                    }
                    point = 0;
                    genv::gout.showmouse(false);
                    draw_all(true);
                }
            }
        }
    } else if (status == WIN) {
        draw_win();
    } else if (status == LOSE) {
        draw_lose();
    }
    frame_counter++;
}

void BrickBreaker::draw_all(bool init) {
    if (init) {
        genv::gout << genv::move_to(0, 0) << genv::color(background[0], background[1], background[2])
                   << genv::box_to(X - 1, Y - 1);
        for (auto &brick: bricks) {
            if (brick.is_visible())
                brick.draw();
        }
    }
    if (frame_counter % 7 == 0 || collision || init) { // ~60 fps
        ball.draw();
        slider.draw();
        genv::gout << genv::refresh;
    }
}

void BrickBreaker::draw_menu() {
    menu.show(X / 2 - menu.width() / 2, Y / 2 - menu.height() * 3 / 4);
    newGame.draw();
    genv::gout << refresh;
    status = MENUDRIWEN;
}

void BrickBreaker::draw_lose() {
    game_over.show(X / 2 - game_over.width() / 2, Y / 2 - game_over.height() / 3);
    newGame.set_position(X / 2 - newGame.get_width() / 2, Y / 2 + game_over.height() - newGame.get_height() / 2);
    newGame.draw();
    slider.draw();
    ball.draw();
    genv::gout << refresh;
    status = MENUDRIWEN;
}

void BrickBreaker::draw_win() {
    ball.draw();
    slider.draw();
    win.show(X / 2 - win.width() / 2, Y / 2 - win.height());
    newGame.set_position(X / 2 - newGame.get_width() / 2, Y / 2 + newGame.get_height() / 2);
    newGame.draw();
    genv::gout << refresh;
    status = MENUDRIWEN;
}


#endif //UNTITLED_BRICKBREAKER_HPP
