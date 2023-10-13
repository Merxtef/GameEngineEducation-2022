#pragma once

#include <sol/sol.hpp>

#include "IScriptProxy.h"


class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
private:
	sol::state lua_script;

public:
	CScriptProxy(const char* filename);

	virtual float UpdateSpeed(bool isRight, bool isLeft, float dt, float speed, float currentSpeed) override;
};

