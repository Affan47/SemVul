SetIntAndUpdateVideo(int *ptr, int value)
{
	int old_value = *ptr;
	if (old_value != value) {
		*ptr = value;
		if (!VIDEOMODE_Update()) {
			*ptr = old_value;
			return FALSE;
		}
	}
	return TRUE;
}
