#include "lib/myLib.hpp"

C_Bar::C_Bar(int x_, int y_, float xSize_, float ySize_, int color_, int b_color_ )
{
    position.x = x_;
    position.y = y_;

    xSize = xSize_;
    ySize = ySize_;

    color = color_;
    b_color = b_color_;
}

void C_Bar::setPosition(int x_, int y_)
{
    position.x = x_;
    position.y = y_;
}

void C_Bar::setColor(int color_)
{
    color = color_;
}

void C_Bar::setSize(int x_, int y_)
{
    xSize = x_;
    ySize = y_;
}

void C_Bar::setPercentage(float percentage_)
{
    percentage = percentage_;
    if (percentage < 0) percentage = 0;
}

void C_Bar::update()
{
    setfillstyle(SOLID_FILL, b_color);
    bar(position.x - 1, position.y - 1, position.x + (int)xSize + 1, position.y + (int)ySize + 1);

    setfillstyle(SOLID_FILL, color);
    bar(position.x, position.y, position.x + (int)(xSize * percentage), position.y + (int)(ySize));
}