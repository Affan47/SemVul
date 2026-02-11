engine_msec_per_move (char *line)
{
	if (!line) return;
	time_per_move = atoi (line);
	if (time_per_move < 0)
		time_per_move = 3000;
}
