
#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include "CommonFunc.h"

class BaseObject {
public:
    BaseObject();
    ~BaseObject();
    virtual SDL_Texture* CreatImage(const char* path, SDL_Renderer* screen);
    virtual bool LoadImage(const char* path, SDL_Renderer* screen);
    virtual void Render(SDL_Renderer* screen, const SDL_Rect* src, double angle, SDL_Point* center, SDL_RendererFlip flip);

    void Free();
    void SetRect(const int& x, const int& y, const int& w, const int& h) {
        rect_.x = x, rect_.y = y;
        rect_.w = w;
        rect_.h = h;
    };
    SDL_Rect GetRect() const {
        return rect_;
    }
    SDL_Texture* GetObject() {
        return object_;
    }
protected:
    SDL_Texture* object_;
    SDL_Rect rect_;
    int width;
    int height;
};


#endif
