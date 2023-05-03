#ifndef MAINMENU_H
#define MAINMENU_H

#include "BaseObject.h"

class MainMenu {
private:
    bool isClicked;
    BaseObject menuBackground;
public:
    MainMenu();
    ~MainMenu();
    void FreeMenu();
    bool Init(SDL_Renderer* screen);
    int EventHandling(SDL_Event& e);
    void RenderMenu(SDL_Renderer* screen);
    bool getClicked();
};

#endif // MAINMENU_H
