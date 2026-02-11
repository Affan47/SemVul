check_system_inodes(struct gfs2_sbd *sdp)
{
	int journal_count;


	if (!sdp->gfs1) {
		fsck_blockmap_set(sdp->master_dir,
				  sdp->master_dir->i_di.di_num.no_addr,
				  "master", gfs2_inode_dir);
		if (check_system_inode(sdp, &sdp->master_dir, "master",
				       build_master, gfs2_inode_dir)) {
			stack;
			return -1;
		}
	}


	fsck_blockmap_set(sdp->md.rooti, sdp->md.rooti->i_di.di_num.no_addr,
			  "root", gfs2_inode_dir);
	if (check_system_inode(sdp, &sdp->md.rooti, "root", build_root,
			       gfs2_inode_dir)) {
		stack;
		return -1;
	}
	if (!sdp->gfs1 &&
	    check_system_inode(sdp, &sdp->md.inum, "inum", build_inum,
			       gfs2_inode_file)) {
		stack;
		return -1;
	}
	if (check_system_inode(sdp, &sdp->md.statfs, "statfs", build_statfs,
			       gfs2_inode_file)) {
		stack;
		return -1;
	}
	if (check_system_inode(sdp, &sdp->md.jiinode, "jindex", build_jindex,
			       (sdp->gfs1 ? gfs2_inode_file : gfs2_inode_dir))) {
		stack;
		return -1;
	}
	if (check_system_inode(sdp, &sdp->md.riinode, "rindex", build_rindex,
			       gfs2_inode_file)) {
		stack;
		return -1;
	}
	if (check_system_inode(sdp, &sdp->md.qinode, "quota", build_quota,
			       gfs2_inode_file)) {
		stack;
		return -1;
	}
	if (!sdp->gfs1 &&
	    check_system_inode(sdp, &sdp->md.pinode, "per_node",
			       build_per_node, gfs2_inode_dir)) {
		stack;
		return -1;
	}


	journal_count = sdp->md.journals;

	if (sdp->gfs1) {


		incr_link_count(sdp->md.statfs->i_di.di_num, NULL,
				_("gfs1 statfs inode"));
		incr_link_count(sdp->md.jiinode->i_di.di_num, NULL,
				_("gfs1 jindex inode"));
		incr_link_count(sdp->md.riinode->i_di.di_num, NULL,
				_("gfs1 rindex inode"));
		incr_link_count(sdp->md.qinode->i_di.di_num, NULL,
				_("gfs1 quota inode"));
		return 0;
	}
	for (sdp->md.journals = 0; sdp->md.journals < journal_count;
	     sdp->md.journals++) {
		char jname[16];

		sprintf(jname, "journal%d", sdp->md.journals);
		if (check_system_inode(sdp, &sdp->md.journal[sdp->md.journals],
				       jname, build_a_journal,
				       gfs2_inode_file)) {
			stack;
			return -1;
		}
	}

	return 0;
}
