ah_find_elm(HASH *ahd, void *celem)
{
	void		*pfirst;
	void		*p;
	int		i;

	pfirst = ah_find(ahd, *((int4 *) celem));

	if ((pfirst == 0) || (ahd->ah_cmp == 0) ||
			((*(ahd->ah_cmp))(pfirst, celem) == 0)) {
		return(pfirst);
	}


	if (ahd->ah_mode & AHLRU) {
		i = ((int) ((char *) pfirst - (char *) ahd->ah_table)) /
						ahd->ah_elemsize;
		--(ahd->ah_lru)[i];
	}


	p = ah_next(ahd, pfirst);
	if (p == 0) p = ah_top(ahd);

	for ( ; p != pfirst; p = ah_next(ahd, p)) {

		if (p == 0) p = ah_top(ahd);


		if ((*(ahd->ah_cmp))(p, celem) == 0) {

			if (ahd->ah_mode & AHLRU) {
				i = ((int) ((char *) p -
					(char *) ahd->ah_table)) /
						ahd->ah_elemsize;
				--(ahd->ah_lru)[i];
			}

			return(p);
		}
	}


	errno = EINVAL;
	return((void *) 0);
}
