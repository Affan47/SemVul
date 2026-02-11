last_del(const char *uid) {
	struct last *ll;

	for (ll = lasts; ll; ll = ll->next) {
		if (!xstrcasecmp(uid, ll->uid))
			ll = lasts_removei(ll);
	}
}
