#include "CommonFunc.h"
int CommonFunc::RanGen(int min_, int max_) {
    return rand()%(max_ - min_ + 1) + min_;
}

bool CommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2) {
    SDL_bool collision = SDL_HasIntersection(&object1, &object2);
    return collision;
}


