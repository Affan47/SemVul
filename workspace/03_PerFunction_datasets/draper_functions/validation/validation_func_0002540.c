inorec_agg_search_insert(uint32_t inonum,
			     struct fsck_inode_record **addr_inorecptr)
{
	int iasi_rc = FSCK_OK;
	struct fsck_inode_record *new_inorecptr;
	int I_am_logredo = 0;

	*addr_inorecptr = NULL;
	if (agg_recptr->AIT_ext0_tbl == NULL) {
		iasi_rc = FSCK_INTERNAL_ERROR_48;
		fsck_send_msg(fsck_INTERNALERROR, iasi_rc, inonum, 0, 0);
	} else {

		if (agg_recptr->AIT_ext0_tbl->inorectbl[inonum] == NULL) {

			iasi_rc =
			    alloc_wrksp(inode_record_length, dynstg_inorec,
					I_am_logredo, (void **) &new_inorecptr);
			if (iasi_rc == FSCK_OK) {
				new_inorecptr->inonum = inonum;
				agg_recptr->AIT_ext0_tbl->inorectbl[inonum] =
				    new_inorecptr;
			}
		}
		if (iasi_rc == FSCK_OK) {
			*addr_inorecptr =
			    agg_recptr->AIT_ext0_tbl->inorectbl[inonum];
		}
	}

	return (iasi_rc);
}
