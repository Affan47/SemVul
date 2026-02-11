csync_insynctest_all(int init_run, int auto_diff, const char *filename)
{
	struct textlist *myname_list = 0, *myname;
	struct csync_group *g;
	int ret = 1;

	if (auto_diff && filename) {
		struct peer *pl = csync_find_peers(filename, 0);
		int pl_idx;

		for (pl_idx=0; pl && pl[pl_idx].peername; pl_idx++)
			csync_diff(pl[pl_idx].myname, pl[pl_idx].peername, filename);

		free(pl);
		return ret;
	}

	for (g = csync_group; g; g = g->next) {
		if ( !g->myname ) continue;
		for (myname=myname_list; myname; myname=myname->next)
			if ( !strcmp(g->myname, myname->value) ) goto skip_this_myname;
		textlist_add(&myname_list, g->myname, 0);
skip_this_myname: ;
	}

	for (myname=myname_list; myname; myname=myname->next)
	{
		struct textlist *peername_list = 0, *peername;
		struct csync_group_host *h;

		for (g = csync_group; g; g = g->next) {
			if ( !g->myname || strcmp(myname->value, g->myname) ) continue;

			for (h=g->host; h; h=h->next) {
				for (peername=peername_list; peername; peername=peername->next)
					if ( !strcmp(h->hostname, peername->value) ) goto skip_this_peername;
				textlist_add(&peername_list, h->hostname, 0);
skip_this_peername:		;
			}
		}

		for (peername=peername_list; peername; peername=peername->next) {
			csync_debug(1, "Running in-sync check for %s <-> %s.\n", myname->value, peername->value);
			if ( !csync_insynctest(myname->value, peername->value, init_run, auto_diff, filename) ) ret=0;
		}

		textlist_free(peername_list);
	}

	textlist_free(myname_list);

	return ret;
}
