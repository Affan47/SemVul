ocfs2_get_dentry(struct super_block *sb,
		struct ocfs2_inode_handle *handle)
{
	struct inode *inode;
	struct ocfs2_super *osb = OCFS2_SB(sb);
	u64 blkno = handle->ih_blkno;
	int status, set;
	struct dentry *result;

	trace_ocfs2_get_dentry_begin(sb, handle, (unsigned long long)blkno);

	if (blkno == 0) {
		result = ERR_PTR(-ESTALE);
		goto bail;
	}

	inode = ocfs2_ilookup(sb, blkno);


	if (inode)
		goto check_gen;


	status = ocfs2_nfs_sync_lock(osb, 1);
	if (status < 0) {
		mlog(ML_ERROR, "getting nfs sync lock(EX) failed %d\n", status);
		goto check_err;
	}

	status = ocfs2_test_inode_bit(osb, blkno, &set);
	if (status < 0) {
		if (status == -EINVAL) {


			status = -ESTALE;
		} else
			mlog(ML_ERROR, "test inode bit failed %d\n", status);
		goto unlock_nfs_sync;
	}

	trace_ocfs2_get_dentry_test_bit(status, set);

	if (!set) {
		status = -ESTALE;
		goto unlock_nfs_sync;
	}

	inode = ocfs2_iget(osb, blkno, 0, 0);

unlock_nfs_sync:
	ocfs2_nfs_sync_unlock(osb, 1);

check_err:
	if (status < 0) {
		if (status == -ESTALE) {
			trace_ocfs2_get_dentry_stale((unsigned long long)blkno,
						     handle->ih_generation);
		}
		result = ERR_PTR(status);
		goto bail;
	}

	if (IS_ERR(inode)) {
		mlog_errno(PTR_ERR(inode));
		result = (void *)inode;
		goto bail;
	}

check_gen:
	if (handle->ih_generation != inode->i_generation) {
		iput(inode);
		trace_ocfs2_get_dentry_generation((unsigned long long)blkno,
						  handle->ih_generation,
						  inode->i_generation);
		result = ERR_PTR(-ESTALE);
		goto bail;
	}

	result = d_obtain_alias(inode);
	if (IS_ERR(result))
		mlog_errno(PTR_ERR(result));

bail:
	trace_ocfs2_get_dentry_end(result);
	return result;
}
