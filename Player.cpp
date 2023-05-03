#include "Player.h"

Player::Player() {
    is_dead = false;
    g = 0.5;
    accelerator = 0;
    jumpHeight = -8;
    jumpState = false;
    yPos = p_y;
}

Player::~Player() {
    Free();
}


void Player::getJumpTime() {
    jumptimer = (double)SDL_GetTicks();
}


void Player::Render_Player(SDL_Renderer* screen) {

    BaseObject::Render(screen, NULL, 0, NULL, SDL_FLIP_NONE);
}


void Player::Gravity() {
    if (jumpState) {
        jumpHeight = jumpHeight + g;
        yPos = yPos + jumpHeight + g;
        if (yPos < 0) {
            yPos = 0;
        }
        BaseObject::SetRect(p_x, yPos, p_w, p_h);

        if (jumpHeight > 0) {
            jumpState = false;
            jumpHeight = -8;
        }
    } else {
        accelerator = accelerator + 0.2;
        yPos = yPos + g + accelerator;
        if (yPos > GROUND_MAP - rect_.h) {
            yPos = GROUND_MAP - rect_.h;
            is_dead = true;
        }
        BaseObject::SetRect(p_x, yPos, p_w, p_h);
    }
}

void Player::jump() {
    getJumpTime();
    if (jumptimer - lastjump > 50 && !is_dead) {
        accelerator = 0;
        jumpState = true;
        Mix_Chunk* fly = Mix_LoadWAV("Sound//fly.wav");
        Mix_PlayChannel(-1, fly, 0);
        lastjump = jumptimer;
    } else {
        Gravity();
    }
}

void Player::HandleInputEvent(SDL_Event e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE) {
            if(!jumpState) {
                jump();
            } else {
                Gravity();
            }
        }
    } else {
        Gravity();
    }
}

bool Player::LoadImage_Player(const char* path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImage(path, screen);
    return ret;
}


bool Player::GetFalling() {
    if (getRectPlayer().y + getRectPlayer().h == GROUND_MAP) {
        return true;
    }
    return false;
}

