istgt_lu_access(CONN_Ptr conn, ISTGT_LU_Ptr lu, const char *iqn, const char *addr)
{
	ISTGT_Ptr istgt;
	INITIATOR_GROUP *igp;
	int pg_tag;
	int ig_tag;
	int rc;
	int i, j, k;

	if (conn == NULL || lu == NULL || iqn == NULL || addr == NULL)
		return 0;
	istgt = conn->istgt;
	pg_tag = conn->portal.tag;

	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "pg=%d, iqn=%s, addr=%s\n",
				  pg_tag, iqn, addr);
	for (i = 0; i < lu->maxmap; i++) {

		if (pg_tag != lu->map[i].pg_tag)
			continue;

		ig_tag = lu->map[i].ig_tag;
		igp = istgt_lu_find_initiatorgroup(istgt, ig_tag);
		if (igp == NULL) {
			ISTGT_ERRLOG("LU%d: ig_tag not found\n", lu->num);
			continue;
		}
		for (j = 0; j < igp->ninitiators; j++) {

			if (igp->initiators[j][0] == '!'
			    && (strcasecmp(&igp->initiators[j][1], "ALL") == 0
				|| strcasecmp(&igp->initiators[j][1], iqn) == 0)) {

				ISTGT_WARNLOG("access denied from %s (%s) to %s (%s:%s,%d)\n",
				    iqn, addr, conn->target_name, conn->portal.host,
				    conn->portal.port, conn->portal.tag);
				return 0;
			}

			if (strcasecmp(igp->initiators[j], "ALL") == 0
			    || strcasecmp(igp->initiators[j], iqn) == 0) {

				if (igp->nnetmasks == 0) {

					return 1;
				}
				for (k = 0; k < igp->nnetmasks; k++) {
					ISTGT_TRACELOG(ISTGT_TRACE_DEBUG,
					    "netmask=%s, addr=%s\n",
					    igp->netmasks[k], addr);
					rc = istgt_lu_allow_netmask(igp->netmasks[k], addr);
					if (rc > 0) {

						return 1;
					}
				}

			}
		}
	}


	ISTGT_WARNLOG("access denied from %s (%s) to %s (%s:%s,%d)\n",
	    iqn, addr, conn->target_name, conn->portal.host,
	    conn->portal.port, conn->portal.tag);
	return 0;
}
