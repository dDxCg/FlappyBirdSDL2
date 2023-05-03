#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommonFunc.h"




class Player : public BaseObject {
public:
    Player();
    ~Player();

    bool LoadImage_Player(const char* path, SDL_Renderer* screen);
    void Render_Player(SDL_Renderer* screen);
    void HandleInputEvent(SDL_Event events);

    void Gravity();
    bool GetDead() const {
        return is_dead;
    }
    bool GetFalling();
    void setDead(bool is_dead_) {
        is_dead = is_dead_;
    }
    SDL_Rect getRectPlayer() const {
        return this->GetRect();
    }
    void getJumpTime();
    void jump();


private:
    int yPos;
    double jumpHeight;
    double g;
    double accelerator;
    bool is_dead;
    bool jumpState;
    double lastjump;
    double jumptimer;



};


#endif
