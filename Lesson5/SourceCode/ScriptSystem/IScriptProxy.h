#pragma once
#include "Common.h"

class SCRIPTSYSTEM_API IScriptProxy
{
public:
	virtual float UpdateSpeed(bool isRight, bool isLeft, float dt, float speed, float currentSpeed) = 0;
};