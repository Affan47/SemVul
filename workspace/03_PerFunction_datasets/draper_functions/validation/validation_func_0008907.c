istgt_build_portal_array(ISTGT_Ptr istgt)
{
	CF_SECTION *sp;
	const char *val;
	int rc;
	int i;

	sp = istgt->config->section;
	while (sp != NULL) {
		if (sp->type == ST_PORTALGROUP) {
			if (sp->num == 0) {
				ISTGT_ERRLOG("Group 0 is invalid\n");
				return -1;
			}
			if (sp->num > ISTGT_PG_TAG_MAX) {
				ISTGT_ERRLOG("tag %d is invalid\n", sp->num);
				return -1;
			}

			val = istgt_get_val(sp, "Comment");
			if (val != NULL) {
				ISTGT_TRACELOG(ISTGT_TRACE_DEBUG,
				    "Comment %s\n", val);
			}
			for (i = 0; ; i++) {
				val = istgt_get_nval(sp, "Portal", i);
				if (val == NULL)
					break;
				rc = istgt_add_portal(istgt, sp, i);
				if (rc < 0) {
					ISTGT_ERRLOG("add_portal() failed\n");
					return -1;
				}
			}
		}
		sp = sp->next;
	}
	return 0;
}
