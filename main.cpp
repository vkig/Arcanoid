#include "graphics.hpp"
#include "src/BrickBreaker.hpp"

using namespace genv;

const int XX = 640;
const int YY = 480;

int main() {
    gout.open(XX, YY);
    event ev;
    genv::gout.load_font("assets/myfont.ttf", 32);
    int w = 300;
    int h = 50;
    Button b1(XX / 2 - w / 2, YY / 4 - h / 2, w, h, "Windowed");
    Button b2(XX / 2 - w / 2, YY * 3 / 4 - h / 2, w, h, "Fullscreen");
    b1.draw();
    b2.draw();
    gout << refresh;
    bool stop = false;
    bool full = false;
    while (gin >> ev && !stop && ev.keycode != key_escape) {
        if (ev.type == ev_mouse) {
            if (ev.button == btn_left && (b1.mouse_on_it(ev.pos_x, ev.pos_y) || b2.mouse_on_it(ev.pos_x, ev.pos_y))) {
                if (b2.mouse_on_it(ev.pos_x, ev.pos_y))
                    full = true;
                stop = true;
            }
        }
    }
    if (full) {
        gout.close();
        gout.open(XX, YY, full);
    } else {
        gout << move_to(0, 0) << color(0, 0, 0) << box_to(XX - 1, YY - 1);
    }
    gout << refresh;
    BrickBreaker br(XX, YY);
    gin.timer(2);
    gout.set_title("BrickBreaker");
    while (gin >> ev && ev.keycode != key_escape) {
        br.event_manager(ev);
    }
    return 0;
}
