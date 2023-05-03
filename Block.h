#ifndef BLOCK_H
#define BLOCK_H


#include "BaseObject.h"


#define blBlank 150
#define blDistance 250
#define bl_w 64
#define bl_h 400

class Block : public BaseObject {
private:
    bool is_back;
    int xPos;
    int yPos;
public:
    Block();
    ~Block();

    bool load_Block(const char* path, SDL_Renderer *screen);
    void show_Block(SDL_Renderer *screen);

    void setPos(const int& x, const int& y);
    void setX(const int& x);

    void Run(UINT& x_vel);
    void setBack(bool is_back_) {
        is_back = is_back_;
    }
    bool getBack() const {
        return is_back;
    }

    SDL_Rect getRectPos() const {
        return this->GetRect();
    }
} ;


class BlockPair {
private:
    Block top;
    Block bot;
    UINT x_vel;
    bool is_back;
    bool is_passed;
    SDL_Rect score_rect;
public:

    BlockPair();
    ~BlockPair();

    bool InitBlock(SDL_Renderer *screen, const int& x);
    void Render_Blocks(SDL_Renderer *screen);

    void Moving();

    bool GetBack_Pair() const {
        return is_back;
    }
    void setBack_Pair(bool is_back_);

    void setPass(const bool& is_passed_) {
        is_passed = is_passed_;
    }
    bool getPass() const {
        return is_passed;
    }

    bool checkCol(SDL_Rect rect_player);


    void getRectScoreRec();
    bool checkPass(SDL_Rect rect);

    SDL_Rect getTop();


};

class BlockList {
private:
    std::vector <BlockPair*> BlockLs;
    UINT endBlock_mark;
    INT score;
    SDL_Rect rect_player;
    bool is_col;
    bool is_stop;
public:
    BlockList();
    ~BlockList();

    void FreeList();
    bool InitList(SDL_Renderer *screen);
    void RenderList(SDL_Renderer *screen);

    void SetStop(const bool& stop_);
    bool getCol() const {
        return is_col;
    }

    INT getScore() const {
        return score;
    }
    void setPlayerRect(SDL_Rect rect_player_) {
        rect_player = rect_player_;
    }
};

#endif
