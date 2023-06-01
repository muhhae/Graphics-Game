#ifndef _SCREEN_HPP
#define _SCREEN_HPP

#include "myLib.hpp"

class gameScreen
{
    private :
        int frameBuffer = 2;
        int activePage = 0;
        int visualPage = 1;
    public :
        gameScreen();
        ~gameScreen();
        void screenUpdate();
};

#endif