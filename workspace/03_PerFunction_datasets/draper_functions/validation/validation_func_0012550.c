t4_cleanup_clip_tbl(struct adapter *adap)
{
	struct clip_tbl *ctbl = adap->clipt;

	if (ctbl) {
		if (ctbl->cl_list)
			t4_free_mem(ctbl->cl_list);
		t4_free_mem(ctbl);
	}
}
