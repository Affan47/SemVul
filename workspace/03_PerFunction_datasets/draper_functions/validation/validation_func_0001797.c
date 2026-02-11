ocfs2_xattr_ibody_init(struct inode *inode,
				  struct buffer_head *di_bh,
				  struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	unsigned int xattrsize = osb->s_xattr_inline_size;

	if (!ocfs2_xattr_has_space_inline(inode, di)) {
		ret = -ENOSPC;
		goto out;
	}

	ret = ocfs2_journal_access_di(ctxt->handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}


	if (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		struct ocfs2_inline_data *idata = &di->id2.i_data;
		le16_add_cpu(&idata->id_count, -xattrsize);
	} else if (!(ocfs2_inode_is_fast_symlink(inode))) {
		struct ocfs2_extent_list *el = &di->id2.i_list;
		le16_add_cpu(&el->l_count, -(xattrsize /
					     sizeof(struct ocfs2_extent_rec)));
	}
	di->i_xattr_inline_size = cpu_to_le16(xattrsize);

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_INLINE_XATTR_FL|OCFS2_HAS_XATTR_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	ocfs2_journal_dirty(ctxt->handle, di_bh);

out:
	return ret;
}
