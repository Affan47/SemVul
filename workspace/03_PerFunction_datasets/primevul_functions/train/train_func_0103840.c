static int calcomp(struct calendar *pjd1, struct calendar *pjd2)
{
	int32_t diff;

	diff = pjd1->year - pjd2->year;
	if (diff < 0) return -1; else if (diff > 0) return 1;

	diff = pjd1->month - pjd2->month;
	if (diff < 0) return -1; else if (diff > 0) return 1;

	diff = pjd1->monthday - pjd2->monthday;
	if (diff < 0) return -1; else if (diff > 0) return 1;

	diff = pjd1->hour - pjd2->hour;
	if (diff < 0) return -1; else if (diff > 0) return 1;
	diff = pjd1->minute - pjd2->minute;
	if (diff < 0) return -1; else if (diff > 0) return 1;
	diff = pjd1->second - pjd2->second;
	if (diff < 0) return -1; else if (diff > 0) return 1;

	return 0;
}
