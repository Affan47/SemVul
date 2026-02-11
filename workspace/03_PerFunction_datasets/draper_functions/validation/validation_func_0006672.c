changed(void)
{
	GET_SENDER();

	if (THIS->no_change)
		return;

	THIS->length = -1;

	GB.Raise(THIS, EVENT_Change, 0);
}
