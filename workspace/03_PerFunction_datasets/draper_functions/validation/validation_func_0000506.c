store_global_handler(Handler &h)
{
    for (int i = 0; i < nglobalh; i++)
	if (globalh[i]._name == h._name) {
	    h.combine(globalh[i]);
	    globalh[i] = h;
	    globalh[i]._use_count = 1;
	    return;
	}

    if (nglobalh >= globalh_cap) {
	int n = (globalh_cap ? 2 * globalh_cap : 4);
	Handler *hs = new Handler[n];
	if (!hs)
	    return;
	for (int i = 0; i < nglobalh; i++)
	    hs[i] = globalh[i];
	delete[] globalh;
	globalh = hs;
	globalh_cap = n;
    }

    globalh[nglobalh] = h;
    globalh[nglobalh]._use_count = 1;
    nglobalh++;
}
