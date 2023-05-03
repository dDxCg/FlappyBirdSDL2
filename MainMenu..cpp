#include "MainMenu.h"

MainMenu::MainMenu() {
    isClicked = false;
}

bool MainMenu::Init(SDL_Renderer* screen) {
    bool ret = menuBackground.LoadImageA("Texture//MainMenu.png", screen);
    return ret;
}

int MainMenu::EventHandling(SDL_Event& e) {
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
        return -1;
    } else if (e.type == SDL_MOUSEBUTTONDOWN && e.motion.x > 285 && e.motion.x < 510 && e.motion.y > 470 && e.motion.y < 565) {
        isClicked = true;
    }
    return 0;
}

void MainMenu::RenderMenu(SDL_Renderer* screen) {
    menuBackground.Render(screen, NULL, 0, NULL, SDL_FLIP_NONE);
}

bool MainMenu::getClicked() {
    return isClicked;
}

void MainMenu::FreeMenu() {
    menuBackground.Free();
    isClicked = false;
}

MainMenu::~MainMenu() {
    FreeMenu();
}
