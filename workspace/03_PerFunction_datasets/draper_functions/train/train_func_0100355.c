cc_timedata_max_mag(struct cc_timedata *d, double min_time, double max_time)
{
	int	i;
	double	max;
	int	max_i = -1;
	int	set = 0;

	if (d->num == 0)
		return -1;
	for (i = 0; i < d->num; i++)
		if (min_time <= d->data[i].time && d->data[i].time <= max_time)
			if (!set || fabs(d->data[i].value) > max) {
				max_i = i;
				max = fabs(d->data[i].value);
				set = 1;
			}
	return max_i;
}
