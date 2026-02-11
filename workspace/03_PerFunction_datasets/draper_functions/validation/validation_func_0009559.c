zcache_free_data (struct zcache *zc)
{
	int i;
	if (zc->zd) {
		for (i = 0; i < zc->zd->tracks; i++) {
			xfree (zc->zd->zdisktracks[i].data);
		}
		xfree (zc->zd);
	}
	xfree (zc->data);
	xfree (zc->name);
}
