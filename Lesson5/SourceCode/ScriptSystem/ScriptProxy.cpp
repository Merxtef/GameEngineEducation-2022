#include "ScriptProxy.h"

#include <fstream>
#include <sstream>

CScriptProxy::CScriptProxy(const char* filename)
{
    std::ifstream file(filename);

    std::ostringstream content;
    content << file.rdbuf();

    lua_script.script(content.str());
}

float CScriptProxy::UpdateSpeed(bool isRight, bool isLeft, float dt, float speed, float currentSpeed)
{
    sol::protected_function move;

    if (isRight != isLeft) {
        // () ? : looks even worse here cos of necessary typecasts
        if (isRight)
            move = lua_script["MovingRight"];
        else
            move = lua_script["MovingLeft"];
    } else {
        move = lua_script["Idling"];
    }

    std::optional<float> value = move(dt, speed, currentSpeed);

    return (value.has_value()) ? value.value() : 0.0f;
}
