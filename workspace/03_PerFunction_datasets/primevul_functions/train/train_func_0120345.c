root_distance(
	struct peer *peer
	)
{
	double	dtemp;


	dtemp = (peer->delay + peer->rootdelay) / 2
		+ LOGTOD(peer->precision)
		  + LOGTOD(sys_precision)
		  + clock_phi * (current_time - peer->update)
		+ peer->rootdisp
		+ peer->jitter;


	if (dtemp < sys_mindisp)
		dtemp = sys_mindisp;
	return (dtemp);
}
