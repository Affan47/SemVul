ShowStartTime(const PROC * proc)
{
	int	procAgeDays;
	char *	cp;


	cp = ctime(&proc->startTimeClock);


	memcpy(showBuffer, cp + 11, 5);
	showBuffer[5] = '\0';

	procAgeDays = (currentTime - proc->startTimeClock)
		/ (60 * 60 * 24);

	if (procAgeDays > 0)
		sprintf(showBuffer + 5, "-%dd", procAgeDays);

	return showBuffer;
}
