// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "INIReader.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    char fKey = 'W';
    char bKey = 'A';
    char lKey = 'S';
    char rKey = 'D';
    char uKey = 'X';
    char dKey = 'C';

    {
        INIReader configReader("../Config/actionmap.ini");

        fKey = configReader.Get("Keyboard", "GoForward", "W")[0];
        bKey = configReader.Get("Keyboard", "GoBack",    "S")[0];
        lKey = configReader.Get("Keyboard", "GoLeft",    "A")[0];
        rKey = configReader.Get("Keyboard", "GoRight",   "D")[0];
        uKey = configReader.Get("Keyboard", "GoUp",      "X")[0];
        dKey = configReader.Get("Keyboard", "GoDown",    "C")[0];
    }

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            timer.Tick();

            float dt = timer.DeltaTime();

            if (GetAsyncKeyState(fKey))
            {
                cube->Move(0, 0, CUBE_SPEED * dt);
            }
            else if (GetAsyncKeyState(bKey))
            {
                cube->Move(0, 0, -CUBE_SPEED * dt);
            }
            else if (GetAsyncKeyState(lKey))
            {
                cube->Move(-CUBE_SPEED * dt, 0, 0);
            }
            else if (GetAsyncKeyState(rKey))
            {
                cube->Move(CUBE_SPEED * dt, 0, 0);
            }
            else if (GetAsyncKeyState(uKey))
            {
                cube->Move(0, CUBE_SPEED * dt, 0);
            }
            else if (GetAsyncKeyState(dKey))
            {
                cube->Move(0, -CUBE_SPEED * dt, 0);
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
