clustfree(devp, clust)
devstat *devp;
long clust;
{
	long next;

	if (clust) for (;;) {
		next = getfatent(devp, clust);
		if (next < 0L || putfatent(devp, clust, 0) < 0) return(-1);
		if (next == ENDCLUST || next == ERRCLUST) break;
		clust = next;
	}

	return(0);
}
