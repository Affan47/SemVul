can_lock()
{
#ifdef Q_OS_UNIX
	bool ok = false;
#ifdef MLOCK_NOT_VOID_PTR
# define MLOCK_TYPE char *
# define MLOCK_TYPE_CAST (MLOCK_TYPE)
#else
# define MLOCK_TYPE void *
# define MLOCK_TYPE_CAST
#endif

	MLOCK_TYPE d = MLOCK_TYPE_CAST malloc(256);
	if(mlock(d, 256) == 0)
	{
		munlock(d, 256);
		ok = true;
	}
	free(d);
	return ok;
#else
	return true;
#endif
}
