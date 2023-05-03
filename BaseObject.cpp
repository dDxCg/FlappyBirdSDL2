
#include "BaseObject.h"


BaseObject::BaseObject() {
    object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject() {
    Free();
}

SDL_Texture* BaseObject::CreatImage(const char* path, SDL_Renderer* screen) {
    Free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface != NULL) {
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (newTexture != NULL) {
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool BaseObject::LoadImage(const char* path, SDL_Renderer* screen) {
    object_ = CreatImage(path, screen);
    return object_ != NULL;
}

void BaseObject::Free() {
    if (object_ != NULL) {
        SDL_DestroyTexture(object_);
        object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void BaseObject::Render(SDL_Renderer* screen, const SDL_Rect* src, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect dest = { rect_.x, rect_.y, rect_.w, rect_.h };
    if (src != NULL) {
        dest.w = src->w;
        dest.h = src->h;
    }
    SDL_RenderCopyEx(screen, object_, src, &dest, angle, center, flip);
}
