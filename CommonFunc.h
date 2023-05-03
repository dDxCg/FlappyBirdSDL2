
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <windows.h>
#include <vector>
#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#include "BaseObject.h"
#include "TextManager.h"


static  SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

#define GROUND_MAP 560
#define GROUND_WIDTH = 80;
#define WIDTH  800
#define HEIGHT  640
#define VEL -2;

#define p_x 265
#define p_y 265
#define p_w 42
#define p_h 30

//Screen
const int FPS = 60;
const int frameDelay = 1000/FPS;


namespace CommonFunc {
int RanGen(int min_, int max_);
bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

}
#endif
