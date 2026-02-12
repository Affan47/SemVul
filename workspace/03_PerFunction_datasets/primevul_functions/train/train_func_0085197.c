canAcceptConnections(int backend_type)
{
	CAC_state	result = CAC_OK;


	if (pmState != PM_RUN && pmState != PM_HOT_STANDBY &&
		backend_type != BACKEND_TYPE_BGWORKER)
	{
		if (Shutdown > NoShutdown)
			return CAC_SHUTDOWN;
		else if (!FatalError && pmState == PM_STARTUP)
			return CAC_STARTUP;
		else if (!FatalError && pmState == PM_RECOVERY)
			return CAC_NOTCONSISTENT;

		else
			return CAC_RECOVERY;
	}


	if (connsAllowed != ALLOW_ALL_CONNS &&
		backend_type == BACKEND_TYPE_NORMAL)
	{
		if (connsAllowed == ALLOW_SUPERUSER_CONNS)
			result = CAC_SUPERUSER;
		else
			return CAC_SHUTDOWN;
	}


	if (CountChildren(BACKEND_TYPE_ALL) >= MaxLivePostmasterChildren())
		result = CAC_TOOMANY;

	return result;
}
