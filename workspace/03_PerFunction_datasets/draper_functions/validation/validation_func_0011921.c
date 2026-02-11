iag_get(int is_aggregate, int which_it, int which_ait, int32_t iag_num,
	    struct iag **addr_iag_ptr)
{
	int iagg_rc = FSCK_OK;
	int64_t imap_logical_block, extent_offset;
	int64_t offset_in_extent = 0;
	struct dinode *imap_inoptr;
	xad_t *xad_ptr;
	int8_t offset_found;
	int which_agg_inode = 0;

	*addr_iag_ptr = NULL;
	if ((agg_recptr->iag_buf_1st_inode == (iag_num << L2INOSPERIAG)) &&
	    (agg_recptr->iag_for_aggregate == is_aggregate) &&
	    (agg_recptr->iag_which_it == which_it)) {


		*addr_iag_ptr = (struct iag *) agg_recptr->iag_buf_ptr;
		goto iagg_exit;
	}


	iagg_rc = iags_flush();
	if (iagg_rc != FSCK_OK)
		goto iagg_exit;


	if (is_aggregate) {

		if (iag_num < agg_recptr->agg_imap.num_iags) {

			which_agg_inode = AGGREGATE_I;
			iagg_rc = ait_special_read_ext1(which_ait);
			if (iagg_rc != FSCK_OK) {

				report_readait_error(iagg_rc,
						     FSCK_FAILED_CANTREADAITEXTH,
						     which_ait);
				iagg_rc = FSCK_FAILED_CANTREADAITEXTH;
			}
		} else {

			iagg_rc = FSCK_IAGNOOOAGGBOUNDS;
		}
	} else {

		if (iag_num < agg_recptr->fset_imap.num_iags) {

			which_agg_inode = FILESYSTEM_I;
			iagg_rc = ait_special_read_ext1(which_ait);
			if (iagg_rc != FSCK_OK) {

				report_readait_error(iagg_rc,
						     FSCK_FAILED_CANTREADAITEXTK,
						     which_ait);
				iagg_rc = FSCK_FAILED_CANTREADAITEXTK;
			}
		} else {

			iagg_rc = FSCK_IAGNOOOFSETBOUNDS;
		}
	}
	if (iagg_rc != FSCK_OK)
		goto iagg_exit;


	imap_inoptr = (struct dinode *)(agg_recptr->ino_buf_ptr +
	     (which_agg_inode * sizeof (struct dinode)));
	imap_logical_block = IAGTOLBLK(iag_num, agg_recptr->log2_blksperpg);
	iagg_rc = xTree_search(imap_inoptr, imap_logical_block, &xad_ptr,
			       &offset_found);
	if (iagg_rc != FSCK_OK)
		goto iagg_exit;


	if (!offset_found) {
		iagg_rc = FSCK_INTERNAL_ERROR_50;
	} else {

		extent_offset = offsetXAD(xad_ptr);
		if (extent_offset != imap_logical_block) {
			offset_in_extent = imap_logical_block - extent_offset;
		}
		agg_recptr->iag_agg_offset = sb_ptr->s_bsize *
		    (addressXAD(xad_ptr) + offset_in_extent);
		iagg_rc = readwrite_device(agg_recptr->iag_agg_offset,
					   agg_recptr->iag_buf_length,
					   &(agg_recptr->iag_buf_data_len),
					   (void *) agg_recptr->iag_buf_ptr,
					   fsck_READ);
		if (iagg_rc == FSCK_OK) {


			ujfs_swap_iag((struct iag *)agg_recptr->iag_buf_ptr);
			agg_recptr->iag_buf_1st_inode = iag_num << L2INOSPERIAG;
			agg_recptr->iag_fsnum = imap_inoptr->di_fileset;
			agg_recptr->iag_for_aggregate = is_aggregate;
			agg_recptr->iag_which_it = which_it;
			*addr_iag_ptr = (struct iag *)agg_recptr->iag_buf_ptr;
		} else {


			fsck_send_msg(fsck_URCVREAD, fsck_ref_msg(fsck_metadata),
				      Vol_Label);


			fsck_send_msg(fsck_ERRONAGG, FSCK_FAILED_READ_IAG,
				      iagg_rc, fsck_READ,
				      (long long)agg_recptr->iag_agg_offset,
				      agg_recptr->iag_buf_length,
				      agg_recptr->iag_buf_data_len);
			iagg_rc = FSCK_FAILED_READ_IAG;
		}
	}

      iagg_exit:
	return (iagg_rc);
}
