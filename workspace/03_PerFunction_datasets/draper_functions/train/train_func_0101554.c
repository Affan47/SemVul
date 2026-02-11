dump_ring(Ring *ring)
{
	char *buf = malloc(256*ring->n);
	int i;

	buf[0] = '\0';
	for (i=0; i<ring->n; i++)
	{
		if (i) strcat(buf, ",");
		sprintf(buf+strlen(buf), "%g %g",
			ring->list[i].x,
			ring->list[i].y);
	}
	return buf;
}
