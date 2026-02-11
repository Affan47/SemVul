uisrch(BW *bw)
{
	if (smode && lastisrch) {
		struct isrch *isrch = lastisrch;

		lastisrch = 0;
		return itype(bw, 'S' - '@', isrch, NULL);
	} else {
		if (globalsrch) {
			rmsrch(globalsrch);
			globalsrch = 0;
		}
		if (lastisrch) {
			lastpat = vstrunc(lastpat, 0);
			lastpat = vsncpy(lastpat, 0, lastisrch->pattern, sLen(lastisrch->pattern));
			rmisrch(lastisrch);
			lastisrch = 0;
		}
		return doisrch(bw, 0);
	}
}
