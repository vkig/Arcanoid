//
// Created by vkig on 2021. 03. 13..
//

#ifndef UNTITLED_PICTURE_HPP
#define UNTITLED_PICTURE_HPP

#include <fstream>
#include <vector>
#include <filesystem>

class Picture {
    std::vector<std::vector<std::vector<int>>> pixels;
    int w = 0;
    int h = 0;
public:
    Picture() = default;

    explicit Picture(const std::string &filename, bool filter = false, int r = 0, int g = 0, int b = 0) {
        std::ifstream f("assets/" + filename);
        if (f.fail()) {
            std::cerr << "Something went wrong while reading the file! Filename: " << filename << std::endl;
        } else {
            int height, width;
            f >> width >> height;
            w = width;
            h = height;
            pixels = std::vector<std::vector<std::vector<int>>>(width, std::vector<std::vector<int>>(height,
                                                                                                     std::vector<int>(3,
                                                                                                                      0)));
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (filter) {
                        auto pix = std::vector<int>(3, 0);
                        f >> pix[0];
                        f >> pix[1];
                        f >> pix[2];
                        if (pix[0] > r && pix[1] > g && pix[2] > b) {
                            pixels[j][i] = std::vector<int>({-1, -1, -1});
                        } else {
                            pixels[j][i] = pix;
                        }
                    } else {
                        for (int k = 0; k < 3; k++) {
                            f >> pixels[j][i][k];
                        }
                    }
                }
            }
        }
    }

    explicit Picture(std::vector<std::vector<std::vector<int>>> _new) {
        pixels = _new;
        w = (int) _new.size();
        h = (int) _new[0].size();
    }

    void show(int x, int y) {
        for (int i = 0; i < width(); i++) {
            for (int j = 0; j < height(); j++) {
                if (pixels[i][j][0] != -1)
                    gout << move_to(i + x, j + y) << color(pixels[i][j][0], pixels[i][j][1], pixels[i][j][2]) << dot;
            }
        }
        gout << refresh;
    }

    [[nodiscard]] int height() const {
        return h;
    }

    [[nodiscard]] int width() const {
        return w;
    }

};

#endif //UNTITLED_PICTURE_HPP
