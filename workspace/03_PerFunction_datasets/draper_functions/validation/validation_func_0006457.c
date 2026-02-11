compute_stoptime()
{
	return MIN(time(0) + timeout, overall_stoptime);
}
