parameter(QScriptContext *context, QScriptEngine *engine)
	{
		switch(context->argumentCount())
		{
		case 1:
			{
				QObject *object = context->argument(0).toQObject();
				if(ProcessHandle *process = qobject_cast<ProcessHandle*>(object))
					return process->processId();
				else
					return context->argument(0).toInt32();
			}
			return -1;
		default:
			throwError(context, engine, "ParameterCountError", tr("Incorrect parameter count"));
			return -1;
		}
	}
