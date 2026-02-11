freeClonedArgv(int argc, char * argv[]) const
{

	if (argv == NULL) return;

	for (int i = 0 ; i < argc + 1 ; ++i)
	{
		if (argv[i] != NULL)
			delete[] argv[i];
	}
	delete[] argv;
}
