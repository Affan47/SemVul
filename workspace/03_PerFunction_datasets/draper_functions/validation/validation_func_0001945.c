locker_destroy(Locker **locker)
{
	if (locker && *locker)
	{
		locker_release(*locker);
		*locker = NULL;
	}

	return NULL;
}
