ocfs2_dx_dir_format_cluster(struct ocfs2_super *osb,
				       handle_t *handle, struct inode *dir,
				       struct buffer_head **dx_leaves,
				       int num_dx_leaves, u64 start_blk)
{
	int ret, i;
	struct ocfs2_dx_leaf *dx_leaf;
	struct buffer_head *bh;

	for (i = 0; i < num_dx_leaves; i++) {
		bh = sb_getblk(osb->sb, start_blk + i);
		if (bh == NULL) {
			ret = -ENOMEM;
			goto out;
		}
		dx_leaves[i] = bh;

		ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), bh);

		ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir), bh,
					      OCFS2_JOURNAL_ACCESS_CREATE);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}

		dx_leaf = (struct ocfs2_dx_leaf *) bh->b_data;

		memset(dx_leaf, 0, osb->sb->s_blocksize);
		strcpy(dx_leaf->dl_signature, OCFS2_DX_LEAF_SIGNATURE);
		dx_leaf->dl_fs_generation = cpu_to_le32(osb->fs_generation);
		dx_leaf->dl_blkno = cpu_to_le64(bh->b_blocknr);
		dx_leaf->dl_list.de_count =
			cpu_to_le16(ocfs2_dx_entries_per_leaf(osb->sb));

		trace_ocfs2_dx_dir_format_cluster(
				(unsigned long long)OCFS2_I(dir)->ip_blkno,
				(unsigned long long)bh->b_blocknr,
				le16_to_cpu(dx_leaf->dl_list.de_count));

		ocfs2_journal_dirty(handle, bh);
	}

	ret = 0;
out:
	return ret;
}
