hsh_rush(struct objhead *oh)
{
	unsigned u;
	struct sess *sp;
	struct waitinglist *wl;

	CHECK_OBJ_NOTNULL(oh, OBJHEAD_MAGIC);
	Lck_AssertHeld(&oh->mtx);
	wl = oh->waitinglist;
	CHECK_OBJ_NOTNULL(wl, WAITINGLIST_MAGIC);
	for (u = 0; u < cache_param->rush_exponent; u++) {
		sp = VTAILQ_FIRST(&wl->list);
		if (sp == NULL)
			break;
		CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
		AZ(sp->wrk);
		VTAILQ_REMOVE(&wl->list, sp, list);
		DSL(0x20, SLT_Debug, sp->vsl_id, "off waiting list");
		if (SES_Schedule(sp)) {


			break;
		}
	}
	if (VTAILQ_EMPTY(&wl->list)) {
		oh->waitinglist = NULL;
		FREE_OBJ(wl);
	}
}
