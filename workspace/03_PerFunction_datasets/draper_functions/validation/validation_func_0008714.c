vrrp_snmp_trackedscript(struct variable *vp, oid *name, size_t *length,
			int exact, size_t *var_len, WriteMethod **write_method)
{
	static unsigned long long_ret;
        oid *target, current[2], best[2];
        int result, target_len;
	int curinstance, curscr;
	element e1, e2;
	vrrp_t *instance;
	tracked_sc_t *scr, *bscr = NULL;

        if ((result = snmp_oid_compare(name, *length, vp->name, vp->namelen)) < 0) {
                memcpy(name, vp->name, sizeof(oid) * vp->namelen);
                *length = vp->namelen;
        }

	*write_method = 0;
	*var_len = sizeof(long);

	if (LIST_ISEMPTY(vrrp_data->vrrp))
		return NULL;


        best[0] = best[1] = MAX_SUBID;
        target = &name[vp->namelen];
        target_len = *length - vp->namelen;
	curinstance = 0;
	for (e1 = LIST_HEAD(vrrp_data->vrrp); e1; ELEMENT_NEXT(e1)) {
		instance = ELEMENT_DATA(e1);
		curinstance++;
		if (target_len && (curinstance < target[0]))
			continue;
		if (bscr)
			break;
		if (LIST_ISEMPTY(instance->track_script))
			continue;
		curscr = 0;
		for (e2 = LIST_HEAD(instance->track_script); e2; ELEMENT_NEXT(e2)) {
			scr = ELEMENT_DATA(e2);
			curscr++;

			current[0] = curinstance;
			current[1] = curscr;

			if ((result = snmp_oid_compare(current, 2, target,
						       target_len)) < 0)
				continue;
			if ((result == 0) && !exact)
				continue;
			if (result == 0) {

				bscr = scr;
				goto trackedscript_found;
			}
			if (snmp_oid_compare(current, 2, best, 2) < 0) {

				memcpy(best, current, sizeof(oid) * 2);
				bscr = scr;


				break;
			}
		}
	}
	if (bscr == NULL)

		return NULL;
	if (exact)

		return NULL;

        memcpy(target, best, sizeof(oid) * 2);
        *length = vp->namelen + 2;
 trackedscript_found:
	switch (vp->magic) {
	case VRRP_SNMP_TRACKEDSCRIPT_NAME:
		*var_len = strlen(bscr->scr->sname);
		return (u_char *)bscr->scr->sname;
	case VRRP_SNMP_TRACKEDSCRIPT_WEIGHT:
		long_ret = bscr->weight;
		return (u_char *)&long_ret;
	}
	return NULL;
}
