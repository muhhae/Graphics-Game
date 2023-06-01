#include "lib/myLib.hpp"

void gameScreen::screenUpdate()
{
    activePage++;
    if (activePage >= frameBuffer) activePage = 0;

    visualPage++;
    if (visualPage >= frameBuffer) visualPage = 0;

    setactivepage(activePage);
    setvisualpage(visualPage);

    cleardevice();
}

gameScreen::gameScreen()
{

}

gameScreen::~gameScreen()
{
    
}