smp_allocx(struct stevedore *st, size_t min_size, size_t max_size,
    struct smp_object **so, unsigned *idx, struct smp_seg **ssg)
{
	struct smp_sc *sc;
	struct storage *ss;
	struct smp_seg *sg;
	unsigned tries;
	uint64_t left, extra;

	CAST_OBJ_NOTNULL(sc, st->priv, SMP_SC_MAGIC);
	assert(min_size <= max_size);

	max_size = IRNUP(sc, max_size);
	min_size = IRNUP(sc, min_size);

	extra = IRNUP(sc, sizeof(*ss));
	if (so != NULL) {
		extra += sizeof(**so);
		AN(idx);
	}

	Lck_Lock(&sc->mtx);
	sg = NULL;
	ss = NULL;
	for (tries = 0; tries < 3; tries++) {
		left = smp_spaceleft(sc, sc->cur_seg);
		if (left >= extra + min_size)
			break;
		smp_close_seg(sc, sc->cur_seg);
		smp_new_seg(sc);
	}
	if (left >= extra + min_size)  {
		if (left < extra + max_size)
			max_size = IRNDN(sc, left - extra);

		sg = sc->cur_seg;
		ss = (void*)(sc->base + sc->next_bot);
		sc->next_bot += max_size + IRNUP(sc, sizeof(*ss));
		sg->nalloc++;
		if (so != NULL) {
			sc->next_top -= sizeof(**so);
			*so = (void*)(sc->base + sc->next_top);

			(*so)->ttl = 0.;
			(*so)->ban = 0.;
			(*so)->ptr = 0;;
			sg->objs = *so;
			*idx = ++sg->p.lobjlist;
		}
		(void)smp_spaceleft(sc, sg);
	}
	Lck_Unlock(&sc->mtx);

	if (ss == NULL)
		return (ss);
	AN(sg);
	assert(max_size >= min_size);


	memset(ss, 0, sizeof *ss);
	ss->magic = STORAGE_MAGIC;
	ss->ptr = PRNUP(sc, ss + 1);
	ss->space = max_size;
	ss->priv = sc;
	ss->stevedore = st;
#ifdef SENDFILE_WORKS
	ss->fd = sc->fd;
#endif
	if (ssg != NULL)
		*ssg = sg;
	return (ss);
}
