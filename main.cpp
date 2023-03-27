#include <SDL.h>

#include "SDL_syswm.h"

#include <ole2.h>
#include <rtscom.h>
#include <rtscom_i.c>

#define EASYTAB_IMPLEMENTATION
#include "easytab.h"

// bool g_bTriedToCreateRTSHandler = false;

// #include <sqlite3.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // if (SDL_Init(SDL_INIT_VIDEO) != 0)
    // {
    //     SDL_Log(u8"SDLの初期化処理に失敗しました。エラーメッセージ: %s", SDL_GetError());
    //     return -1;
    // }
    // printf("%s\n", sqlite3_libversion());

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log(u8"SDLの初期化処理に失敗しました。エラーメッセージ: %s", SDL_GetError());
        return -1;
    }

    SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE); // TODO これがいるんじゃなかったか？

    auto window = SDL_CreateWindow(
        "サンプル",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        0);

    if (window == nullptr)
    {
        SDL_Log(u8"ウィンドウの作成に失敗しました。エラーメッセージ: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hwnd = wmInfo.info.win.window;

    if (EasyTab_Load(hwnd) != EASYTAB_OK)
    {
        // OutputDebugStringA("Tablet init failed\n");
        printf("EASYTAB_OK failed\n");
    }
    else
    {
        printf("EASYTAB_OK\n");
    }
    printf("hwnd = %d\n", hwnd);

    auto is_finished = false;

    while (!is_finished)
    {
        auto event_info = SDL_Event();

        while (SDL_PollEvent(&event_info) == 1)
        {
            switch (event_info.type)
            {
            case SDL_QUIT:
                is_finished = true;
                break;

            // ここで他( SDL_QUIT以外 )のイベントを処理
            case SDL_SYSWMEVENT:
                // case SDL_MOUSEBUTTONDOWN:
                SDL_SysWMmsg *pMsg = event_info.syswm.msg;

                if (EasyTab_HandleEvent(pMsg->msg.win.hwnd, pMsg->msg.win.msg, pMsg->msg.win.lParam, pMsg->msg.win.wParam) == EASYTAB_OK)
                {
                    printf("EASYTAB_OK %f\n", EasyTab->Pressure);
                    // return true; // Tablet event handled

                    // Setup renderer
                    SDL_Renderer *renderer = NULL;
                    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

                    // Set render color to red ( background will be rendered in this color )
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                    // Clear winow
                    // SDL_RenderClear( renderer );

                    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
                    SDL_Rect r;
                    r.x = EasyTab->PosX * 1;
                    printf("%d\n", EasyTab->PosX);
                    r.y = EasyTab->PosY * 1;
                    printf("%d\n", EasyTab->PosY);
                    r.w = EasyTab->Pressure * 10;
                    r.h = -EasyTab->Pressure * 10;

                    // Set render color to blue ( rect will be rendered in this color )
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

                    // Render rect
                    SDL_RenderFillRect(renderer, &r);

                    // Render the rect to the screen
                    SDL_RenderPresent(renderer);
                }

                // if (pMsg && pMsg->msg == WM_SETFOCUS)
                if (pMsg->msg.win.msg == WM_SETFOCUS) // TODO WinUser.h?
                {
                    printf("WM_SETFOCUS\n");

                    // TODO https://stackoverflow.com/questions/24117983/get-window-handle-of-sdl-2-application

                    // SDL_SysWMinfo wmInfo;
                    // SDL_VERSION(&wmInfo.version);
                    // SDL_GetWindowWMInfo(window, &wmInfo);
                    // HWND hwnd = wmInfo.info.win.window;

                    // if( !g_bTriedToCreateRTSHandler )
                    // {
                    //     if (EasyTab_Load(pMsg->msg.win.hwnd) != EASYTAB_OK)
                    //     {
                    //         // OutputDebugStringA("Tablet init failed\n");
                    //         printf("failed\n");
                    //     } else {
                    //         printf("success\n");
                    //     }
                    // }
                    // g_bTriedToCreateRTSHandler = true;

                    // pMsg->msg.win.hwnd
                    // pMsg->msg.win.msg
                    // pMsg->msg.win.wParam
                    // pMsg->msg.win.lParam
                }
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
