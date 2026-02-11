random_add_noise(void *noise, int length)
{
    unsigned char *p = noise;
    int i;

    if (!random_active)
	return;


    while (length >= (HASHINPUT - pool.incomingpos)) {
	memcpy(pool.incomingb + pool.incomingpos, p,
	       HASHINPUT - pool.incomingpos);
	p += HASHINPUT - pool.incomingpos;
	length -= HASHINPUT - pool.incomingpos;
	SHATransform((word32 *) pool.incoming, (word32 *) pool.incomingb);
	for (i = 0; i < HASHSIZE; i++) {
	    pool.pool[pool.poolpos++] ^= pool.incomingb[i];
	    if (pool.poolpos >= POOLSIZE)
		pool.poolpos = 0;
	}
	if (pool.poolpos < HASHSIZE)
	    random_stir();

	pool.incomingpos = 0;
    }

    memcpy(pool.incomingb + pool.incomingpos, p, length);
    pool.incomingpos += length;
}
