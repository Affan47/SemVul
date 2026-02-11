SDLKeyBind(int *retval, char *sdlKeySymIntStr)
{
	int ksym;

	if (retval == NULL || sdlKeySymIntStr == NULL) {
		return FALSE;
	}


	ksym = Util_sscandec(sdlKeySymIntStr);

	if (ksym > SDLK_FIRST && ksym < SDLK_LAST) {
		*retval = ksym;
		return TRUE;
	}
	else {
		return FALSE;
	}
}
