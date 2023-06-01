#ifndef _CBAR_HPP
#define _CBAR_HPP

#include "myLib.hpp"

class C_Bar
{
    private :
        int color;
        int b_color;

        Vector2 position;

        float xSize;
        float ySize;
        float percentage = 1;

    public :
        // C_Bar(){}
        C_Bar(int x_ = 0, int y_ = 0, float xSize_ = 200, float ySize_ = 20, int color_ = RED, int b_color_ = WHITE);
        void setPosition(int x_, int y_);
        void setColor(int color_);
        void setSize(int x_ = 200, int y_ = 20);
        void setPercentage(float percentage_);
        void update();
};

#endif