ELleftbnd(struct Point *p)
{
    int i, bucket;
    struct Halfedge *he;


    bucket = (p->x - xmin) / deltax * ELhashsize;
    if (bucket < 0)
	bucket = 0;
    if (bucket >= ELhashsize)
	bucket = ELhashsize - 1;
    he = ELgethash(bucket);
    if (he == (struct Halfedge *)NULL) {
	for (i = 1; 1; i++) {
	    if ((he = ELgethash(bucket - i)) != (struct Halfedge *)NULL)
		break;
	    if ((he = ELgethash(bucket + i)) != (struct Halfedge *)NULL)
		break;
	}
	totalsearch += i;
    }
    ntry++;

    if (he == ELleftend || (he != ELrightend && right_of(he, p))) {
	do {
	    he = he->ELright;
	} while (he != ELrightend && right_of(he, p));
	he = he->ELleft;
    }
    else
	do {
	    he = he->ELleft;
	} while (he != ELleftend && !right_of(he, p));


    if (bucket > 0 && bucket < ELhashsize - 1) {
	if (ELhash[bucket] != (struct Halfedge *)NULL)
	    ELhash[bucket]->ELrefcnt--;
	ELhash[bucket] = he;
	ELhash[bucket]->ELrefcnt++;
    }
    return (he);
}
