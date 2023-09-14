#pragma once

#include "Common.h"
#include "RenderObject.h"
#include "DefaultGeometry/Cube.h"
#include "Gate.h"

class RENDERENGINE_API CRenderEngine
{
public:
	CRenderEngine() = delete;
	CRenderEngine(HINSTANCE hInstance);
	CRenderEngine(const CRenderEngine& renderEngine) = delete;
	~CRenderEngine();

	void Update();

private:
	HWND InitMainWindow(HINSTANCE hInstance);
	HWND m_hwnd = nullptr;

	long m_Width = 800;
	long m_Height = 600;
	Cube* m_defaultCube;
	StarGate* m_defaultGate;
	InnerRing* m_defaultRing;

	long frame_counter = 0;
};
