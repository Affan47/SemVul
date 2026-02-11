adjust_parents(struct fsck_inode_record *ino_recptr, uint32_t ino_idx)
{
	int adjps_rc = FSCK_OK;
	struct fsck_inode_ext_record *this_ext;
	struct fsck_inode_ext_record *rest_of_list;
	int keep_primary_parent = 0;


	if ((ino_recptr->inode_type == directory_inode)
	    && (ino_recptr->unxpctd_prnts)) {

		if (!ino_recptr->selected_to_rls) {

			if ((ino_recptr->parent_inonum != ROOT_I)
			    || (!agg_recptr->rootdir_rebuilt)) {
				keep_primary_parent = 1;
			}
		}
	} else {


		if (ino_recptr->parent_inonum != 0) {
			if ((ino_recptr->parent_inonum != ROOT_I)
			    || (!agg_recptr->rootdir_rebuilt)) {


				adjps_rc =
				    adjust_parent(ino_idx, ino_recptr,
						  ino_recptr->parent_inonum);
				ino_recptr->parent_inonum = 0;
			}
		}
	}


	this_ext = ino_recptr->ext_rec;
	ino_recptr->ext_rec = NULL;

	while ((adjps_rc == FSCK_OK) && (this_ext != NULL)) {

		rest_of_list = this_ext->next;
		if (this_ext->ext_type != parent_extension) {

			this_ext->next = ino_recptr->ext_rec;
			ino_recptr->ext_rec = this_ext;
		} else {

			if ((this_ext->inonum == ROOT_I)
			    && (agg_recptr->rootdir_rebuilt)) {


				release_inode_extension(this_ext);

			} else if ((keep_primary_parent) &&
				   (this_ext->inonum ==
				    ino_recptr->parent_inonum)) {


				release_inode_extension(this_ext);
				ino_recptr->unxpctd_prnts = 0;

			} else {


				adjps_rc =
				    adjust_parent(ino_idx, ino_recptr,
						  this_ext->inonum);
				release_inode_extension(this_ext);
			}
		}

		this_ext = rest_of_list;
	}
	return (adjps_rc);
}
