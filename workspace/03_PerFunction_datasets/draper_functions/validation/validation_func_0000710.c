pts_to_string(char* str, unsigned long pts)
{
	static char buf[256];
	char* p = (str) ? str : buf;

	int seconds = pts / MPEG_CLOCK_FREQ;
	int fracsec = pts % MPEG_CLOCK_FREQ;

	int minutes = seconds / 60;
	seconds = seconds % 60;

	int hours = minutes / 60;
	minutes = minutes % 60;

	float fps = 30;
	int frame = (int)ceilf(((float)fracsec / (float)MPEG_CLOCK_FREQ) * fps);

	snprintf(p, sizeof(buf), "%d:%02d:%02d:%d", hours, minutes, seconds, frame);
	return p;
}
