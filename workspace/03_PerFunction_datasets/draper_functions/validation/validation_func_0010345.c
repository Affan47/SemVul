fmtExtra(int alrm, int beep)
{
	if (alrm)
		sprintf(buff + strlen(buff), " [ALARM]");
	if (beep)
		sprintf(buff + strlen(buff), " (beep)");
	return buff;
}
