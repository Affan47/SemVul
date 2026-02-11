istgt_build_initiator_group_array(ISTGT_Ptr istgt)
{
	CF_SECTION *sp;
	int rc;

	sp = istgt->config->section;
	while (sp != NULL) {
		if (sp->type == ST_INITIATORGROUP) {
			if (sp->num == 0) {
				ISTGT_ERRLOG("Group 0 is invalid\n");
				return -1;
			}
			rc = istgt_add_initiator_group(istgt, sp);
			if (rc < 0) {
				ISTGT_ERRLOG("add_initiator_group() failed\n");
				return -1;
			}
		}
		sp = sp->next;
	}
	return 0;
}
