onexit()
{
ExitTrap	*p;

	alarm(0);
	for (p=first; p; p=p->next)
		if (p->callcleanup)
			p->cleanup();
}
