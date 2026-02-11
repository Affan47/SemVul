popStrongContext ( void )
{
	int i;

	for (i = stackIndex - 1; i >= 0; --i)
	{
		if (stack[i].kind == ContextStrong)
		{
			stackIndex = i;
			toDoNext = stack[i].callback;
			vStringClear (stack[i].contextName);
			return stack[i].type;
		}
	}

	stackIndex = 0;
	toDoNext = &globalScope;
	return -1;
}
