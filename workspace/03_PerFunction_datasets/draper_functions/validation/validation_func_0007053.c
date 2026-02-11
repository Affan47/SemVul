G_window_overlap(const struct Cell_head *window,
		     double N, double S, double E, double W)
{
    if (window->north <= S)
	return 0;
    if (window->south >= N)
	return 0;

    if (window->proj == PROJECTION_LL) {
	while (E < window->west) {
	    E += 360.0;
	    W += 360.0;
	}
	while (W > window->east) {
	    E -= 360.0;
	    W -= 360.0;
	}
    }

    if (window->east <= W)
	return 0;
    if (window->west >= E)
	return 0;

    return 1;
}
