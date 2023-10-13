#include "ScriptSystem.h"
#include "ScriptProxy.h"


CScriptSystem::CScriptSystem()
{
    return;
}

void CScriptSystem::Update()
{
}

IScriptProxy* CScriptSystem::CreateProxy(const char* filename)
{
    CScriptProxy* proxy = new CScriptProxy(filename);

    return proxy;
}

void CScriptSystem::ProcessScript(IScriptProxy* scriptProxy)
{
}
