
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Player.h"
#include "Block.h"
#include "TextManager.h"
#include "MainMenu.h"

#include <cstdlib>
#include <ctime>

BaseObject g_background;
BaseObject g_ground;


MainMenu menu;


bool Init() {
    BOOL success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    g_window = SDL_CreateWindow("Dumb Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        success = false;
    } else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (g_screen == NULL) {
            success = false;
        } else {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags)) success = false;
        }
        if (TTF_Init() == -1) {
            success = false;
        }
        if (Mix_Init(1) == 0) {
            success = false;
        }
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
            success = false;
        }

    }
    return success;
}

bool LoadBackground() {
    bool ret = g_background.LoadImage("Texture//background.png", g_screen);
    return ret;
}

void close() {
    g_background.Free();
    g_ground.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    menu.FreeMenu();

    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[]) {

    srand(time(0));

    if (!Init()) return -1;
    bool quit = false;

    if (!LoadBackground()) return -1;
    g_ground.LoadImageA("Texture//ground.png", g_screen);
    g_ground.SetRect(0, GROUND_MAP, 800, 80);

    menu.Init(g_screen);
    while (!menu.getClicked()) {
        if (menu.EventHandling(g_event) == -1) {
            quit = true;
            break;
        }
        SDL_RenderClear(g_screen);
        menu.RenderMenu(g_screen);
        SDL_RenderPresent(g_screen);
    }
    menu.FreeMenu();




again_label:

    Player p;
    p.LoadImage_Player("Texture//Player.png", g_screen);
    p.SetRect(265, 265, p_w, p_h);

    BlockList bl_list;
    bl_list.InitList(g_screen);


    Uint32 frameStart = 0;
    int frameTime;

    while (!quit) {
        SDL_PollEvent(&g_event);
        if (g_event.type == SDL_QUIT) {
            quit = true;
        }
        p.HandleInputEvent(g_event);

        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL, 0, NULL, SDL_FLIP_NONE);

        bl_list.setPlayerRect(p.GetRect());
        bool isDead = p.GetDead();
        if (isDead) {
            bl_list.SetStop(true);
        }
        bl_list.RenderList(g_screen);


        bool end_game = bl_list.getCol();
        if (end_game) {
            p.setDead(true);
        }

        p.Render_Player(g_screen);

        //render score
        int score = bl_list.getScore();
        std::string score_str = std::to_string(score);
        TextManager scoreText;
        scoreText.CreateFontA("Font//ARCADE.ttf", 100);
        scoreText.Text(score_str, 255, 255, 255, g_screen);
        scoreText.Render(g_screen, 25, 25);

        g_ground.Render(g_screen, NULL, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(g_screen);



        bool game_over = p.GetFalling();
        if (game_over) {
            Mix_Chunk *failure = Mix_LoadWAV("Sound//failure.wav");
            Mix_PlayChannel(-1, failure, 0);
            Sleep(500);
            menu.Init(g_screen);
            std::string score_menu_str = "Score " + score_str;
            TextManager menu_score;
            menu_score.CreateFontA("Font//ARCADE.ttf", 500);
            scoreText.Text(score_menu_str, 255, 255, 255, g_screen);

            while (!menu.getClicked()) {
                if (menu.EventHandling(g_event) == -1) {
                    quit = true;
                    break;
                }
                SDL_RenderClear(g_screen);
                menu.RenderMenu(g_screen);
                scoreText.Render(g_screen, 230, 320);
                SDL_RenderPresent(g_screen);
            }
            menu.FreeMenu();
            bl_list.FreeList();
            scoreText.CloseFont();
            menu_score.CloseFont();
            goto again_label;
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    close();
    return 0;
}
