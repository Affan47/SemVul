new_adbentry(dns_adb_t *adb) {
	dns_adbentry_t *e;
	isc_uint32_t r;

	e = isc_mempool_get(adb->emp);
	if (e == NULL)
		return (NULL);

	e->magic = DNS_ADBENTRY_MAGIC;
	e->lock_bucket = DNS_ADB_INVALIDBUCKET;
	e->refcnt = 0;
	e->flags = 0;
	e->udpsize = 0;
	e->edns = 0;
	e->plain = 0;
	e->plainto = 0;
	e->to4096 = 0;
	e->to1432 = 0;
	e->to1232 = 0;
	e->to512 = 0;
	e->sit = NULL;
	e->sitlen = 0;
	isc_random_get(&r);
	e->srtt = (r & 0x1f) + 1;
	e->lastage = 0;
	e->expires = 0;
	ISC_LIST_INIT(e->lameinfo);
	ISC_LINK_INIT(e, plink);
	LOCK(&adb->entriescntlock);
	adb->entriescnt++;
	inc_adbstats(adb, dns_adbstats_entriescnt);
	if (!adb->growentries_sent && adb->growentries_sent &&
	    adb->entriescnt > (adb->nentries * 8))
	{
		isc_event_t *event = &adb->growentries;
		inc_adb_irefcnt(adb);
		isc_task_send(adb->task, &event);
		adb->growentries_sent = ISC_TRUE;
	}
	UNLOCK(&adb->entriescntlock);

	return (e);
}
