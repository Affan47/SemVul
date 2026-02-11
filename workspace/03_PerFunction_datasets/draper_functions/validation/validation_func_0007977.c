smp_oc_getobj(struct worker *wrk, struct objcore *oc)
{
	struct object *o;
	struct smp_seg *sg;
	struct smp_object *so;
	struct storage *st;
	uint64_t l;
	int bad;


	assert(oc->methods->getobj == smp_oc_getobj);

	CHECK_OBJ_NOTNULL(oc, OBJCORE_MAGIC);
	if (wrk == NULL)
		AZ(oc->flags & OC_F_NEEDFIXUP);

	CAST_OBJ_NOTNULL(sg, oc->priv, SMP_SEG_MAGIC);
	so = smp_find_so(sg, oc->priv2);

	o = (void*)(sg->sc->base + so->ptr);


	ASSERT_PTR_IN_SILO(sg->sc, o);
	CHECK_OBJ_NOTNULL(o, OBJECT_MAGIC);


	if (!(oc->flags & OC_F_NEEDFIXUP))
		return (o);

	AN(wrk);
	Lck_Lock(&sg->sc->mtx);

	if (oc->flags & OC_F_NEEDFIXUP) {

		o->objcore = oc;

		bad = 0;
		l = 0;
		VTAILQ_FOREACH(st, &o->store, list) {
			bad |= smp_loaded_st(sg->sc, sg, st);
			if (bad)
				break;
			l += st->len;
		}
		if (l != o->len)
			bad |= 0x100;

		if(bad) {
			EXP_Set_ttl(&o->exp, -1);
			so->ttl = 0;
		}

		sg->nfixed++;
		wrk->stats.n_object++;
		wrk->stats.n_vampireobject--;
		oc->flags &= ~OC_F_NEEDFIXUP;
	}
	Lck_Unlock(&sg->sc->mtx);
	EXP_Rearm(o);
	return (o);
}
