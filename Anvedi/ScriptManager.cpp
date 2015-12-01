#include "ScriptManager.h"
#include "QShellEngine_Qt.h"
#include "SignalData.h"
#include "SignalHandle.h"
#include "qshell.h"

using namespace std;

ScriptManager::ScriptManager(SignalData& data, QShell& shell)
{
	InitWorkspace(data, shell);
}

QScriptValue GraphWrapperCtor(QScriptContext *context, QScriptEngine *engine)
{
	if (context->isCalledAsConstructor())
	{
		QScriptValue calleeData = context->callee().data();
		auto data = qobject_cast<SignalData*>(calleeData.toQObject());
		auto signalName = context->argument(0).toString();
		data->getOrInsert(signalName);
		return engine->newQObject(new SignalHandle(move(signalName), *data), QScriptEngine::ScriptOwnership);
	}
	return context->throwError(QScriptContext::TypeError, "graph should be constructed");
}

struct AnvediScriptEngine : QShellEngine_Qt
{
	AnvediScriptEngine(SignalData& data)
	{
		QScriptValue graphWrapperFun = m_engine.newFunction(GraphWrapperCtor);
		graphWrapperFun.setData(m_engine.newQObject(&data));
		m_engine.globalObject().setProperty("graph", graphWrapperFun);
	}
};

void ScriptManager::InitWorkspace(SignalData& data, QShell& shell)
{
	auto scriptEngine = std::make_shared<AnvediScriptEngine>(data);
	shell.SetEngine((shared_ptr<QShellEngine_Qt>)scriptEngine);
}

