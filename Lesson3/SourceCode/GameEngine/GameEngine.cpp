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
#include "InputHandler.h"


static constexpr int CUBE_NUMBER = 100;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();
    InputHandler* inputHandler = new InputHandler();

    //GameObject* cube = new CubeGameObject();
    AbstractCube* cubes[CUBE_NUMBER] = {};

    for (int i = 0; i < CUBE_NUMBER; ++i)
    {
        int type = rand() % 3;
        AbstractCube* cube = nullptr;
        
        if (type == 0)
        {
            cube = new UserControlledCube(4);
        }
        else if (type == 1)
        {
            cube = new JumpingCube(3, -40);
        }
        else
        {
            cube = new SelfMovingCube(12.2f, 2.f);
        }

        cubes[i] = cube;

        float x = ((i / 10) - 4.5f) * 4.f;
        float y = -25.f;
        float z = ((i % 10) - 0.5f) * 4.f;

        cube->SetStart(x, y, z);

        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
    }

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float newPositionX = 0.0f;

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
            inputHandler->Update();

            float t = 0;
            timer.Tick();
            t = sin(timer.TotalTime())*2;

            for (auto& cube : cubes)
            {
                cube->Act(inputHandler, timer.DeltaTime());
            }

            /*
            float velocity = 0.0f;
            if (inputHandler->GetInputState().test(eIC_GoLeft))
                velocity -= 1.0f;
            if (inputHandler->GetInputState().test(eIC_GoRight))
                velocity += 1.0f;
            newPositionX += velocity * timer.DeltaTime();
            cube->SetPosition(newPositionX, 0.0f, 0.0f);
            */

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
