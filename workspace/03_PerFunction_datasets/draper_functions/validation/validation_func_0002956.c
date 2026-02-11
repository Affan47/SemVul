FScreenSpecToString(char *dest, int space, fscreen_scr_t screen)
{
	char s[32];

	if (space <= 0)
	{
		return;
	}
	switch (screen)
	{
	case FSCREEN_GLOBAL:
		strcpy(s, "global screen");
		break;
	case FSCREEN_CURRENT:
		strcpy(s, "current screen");
		break;
	case FSCREEN_PRIMARY:
		strcpy(s, "primary screen");
		break;
	case FSCREEN_XYPOS:
		strcpy(s, "screen specified by xy");
		break;
	default:
		sprintf(s, "%d", screen);
		break;
	}
	strncpy(dest, s, space);
	dest[space - 1] = 0;

	return;
}
