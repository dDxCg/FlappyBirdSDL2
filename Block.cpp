
#include "Block.h"


INT bl_xPos[] = {700, 950, 1200, 1450};

Block::Block() {
    is_back = false;
}
Block::~Block() {};

bool Block::load_Block(const char* path, SDL_Renderer *screen) {
    bool ret = BaseObject::LoadImageA(path, screen);
    return ret;
}
void Block::show_Block(SDL_Renderer *screen) {
    this->Render(screen, NULL, 0, NULL, SDL_FLIP_NONE);
}

void Block::setPos(const int& x, const int& y) {
    this->SetRect(x, y, bl_w, bl_h);
}

void Block::setX(const int& x) {
    SDL_Rect rect = this->GetRect();
    this->SetRect(x, rect.y, bl_w, bl_h);
}

void Block::Run(UINT& x_vel) {
    this->rect_.x += x_vel;
    if (this->rect_.x + this->rect_.w < 0) {
        is_back = true;
    }
}


BlockPair::BlockPair() {
    x_vel = VEL;
    is_back = false;
    is_passed = false;
}

BlockPair::~BlockPair() {}

bool BlockPair::InitBlock(SDL_Renderer *screen, const int& x) {
    bool ret1 = top.load_Block("Texture//top.png", screen);
    bool ret2 = bot.load_Block("Texture//bot.png", screen);

    int ranNum = CommonFunc::RanGen(10,35)*10;

    int top_y = ranNum - bl_h;
    int bot_y = top_y + bl_h + blBlank;
    top.setPos(x, top_y);
    bot.setPos(x, bot_y);

    return ret1 && ret2;
}

void BlockPair::Render_Blocks(SDL_Renderer *screen) {
    top.show_Block(screen);
    bot.show_Block(screen);
}

SDL_Rect BlockPair::getTop() {
    return top.getRectPos();
}

void BlockPair::Moving() {
    top.Run(x_vel);
    bot.Run(x_vel);
    if (top.getBack() || bot.getBack()) {
        is_back = true;
    }
}

void BlockPair::setBack_Pair(bool is_back_) {
    is_back = is_back_;
    top.setBack(is_back);
    bot.setBack(is_back);
}

bool BlockPair::checkCol(SDL_Rect rect_player) {
    bool ret1 = CommonFunc::CheckCollision(rect_player, top.getRectPos());
    bool ret2 = CommonFunc::CheckCollision(rect_player, bot.getRectPos());

    if (ret1 || ret2) {
        return true;
    }
    return false;
}

void BlockPair::getRectScoreRec() {
    SDL_Rect rect_top = top.getRectPos();
    score_rect.x = rect_top.x + rect_top.w;
    score_rect.y = rect_top.y + rect_top.h;
    score_rect.w = 5;
    score_rect.h = blBlank;
}

bool BlockPair::checkPass(SDL_Rect rect) {
    bool ret = CommonFunc::CheckCollision(rect, score_rect);
    return ret;
}


BlockList::BlockList() {
    endBlock_mark = 0;
    is_stop = false;
    is_col = false;
    score = 0;
}

BlockList::~BlockList() {
    FreeList();
}

void BlockList::FreeList() {
    for (int i =0; i < (int)BlockLs.size(); ++i) {
        BlockPair* bl_pair = BlockLs.at(i);
        delete bl_pair;
        bl_pair = NULL;
    }
    BlockLs.clear();
}


bool BlockList::InitList(SDL_Renderer *screen) {
    BlockPair* bl_1 = new BlockPair();
    BlockPair* bl_2 = new BlockPair();
    BlockPair* bl_3 = new BlockPair();
    BlockPair* bl_4 = new BlockPair();

    bool ret1 = bl_1->InitBlock(screen, bl_xPos[0]);
    bool ret2 = bl_2->InitBlock(screen, bl_xPos[1]);
    bool ret3 = bl_3->InitBlock(screen, bl_xPos[2]);
    bool ret4 = bl_4->InitBlock(screen, bl_xPos[3]);

    BlockLs.push_back(bl_1);
    BlockLs.push_back(bl_2);
    BlockLs.push_back(bl_3);
    BlockLs.push_back(bl_4);

    endBlock_mark = 3;
    if (!ret1 || !ret2 || !ret3 || !ret4) {
        return false;
    }
    return true;
}

void BlockList::SetStop(const bool& is_stop_) {
    is_stop = is_stop_;
}

void BlockList::RenderList(SDL_Renderer *screen) {
    for (int i = 0; i < (int)BlockLs.size(); ++i) {
        BlockPair *bl_pair = BlockLs.at(i);
        bl_pair->getRectScoreRec();

        if (!is_stop) {
            bl_pair->Moving();
            bool isBack = bl_pair->GetBack_Pair();
            if (isBack) {
                BlockPair* end_block = BlockLs.at(endBlock_mark);
                SDL_Rect rect_end = end_block->getTop();
                UINT xPos = rect_end.x + blDistance;
                bl_pair->InitBlock(screen, xPos);
                bl_pair->setBack_Pair(false);
                bl_pair->setPass(false);
                endBlock_mark = i;
            }

            bool isCol = bl_pair->checkCol(rect_player);
            if (isCol) {
                is_col = true;
                Mix_Chunk* hit = Mix_LoadWAV("Sound//hit.wav");
                Mix_PlayChannel(-1, hit, 0);

            }

            bool isPass = bl_pair->checkPass(rect_player);
            if (isPass) {
                if(bl_pair->getPass() == false) {
                    ++score;
                    bl_pair->setPass(true);
                    Mix_Chunk* score = Mix_LoadWAV("Sound//score.wav");
                    Mix_PlayChannel(-1, score, 0);
                }
            }
        }
        bl_pair->Render_Blocks(screen);
    }
}
