uih_fixedcolordisable(uih_context * c)
{
#ifdef SCONVERTORS
    if (c->fixedcolor != NULL) {
	int wascycling = 0;
	if (c->cycling)
	    uih_cycling_off(c), wascycling = 1;
	initqueue(c->queue);
	removefilter(c->fixedcolor);
	initqueue(c->queue);
	c->fixedcolor->action->destroyinstance(c->fixedcolor);
	c->fixedcolor = NULL;
	uih_newimage(c);
	if (wascycling)
	    uih_cycling_on(c);
    }
#endif
}
