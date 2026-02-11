_pnfs_return_layout(struct inode *ino)
{
	struct pnfs_layout_hdr *lo = NULL;
	struct nfs_inode *nfsi = NFS_I(ino);
	LIST_HEAD(tmp_list);
	nfs4_stateid stateid;
	int status = 0, empty;
	bool send;

	dprintk("NFS: %s for inode %lu\n", __func__, ino->i_ino);

	spin_lock(&ino->i_lock);
	lo = nfsi->layout;
	if (!lo) {
		spin_unlock(&ino->i_lock);
		dprintk("NFS: %s no layout to return\n", __func__);
		goto out;
	}
	stateid = nfsi->layout->plh_stateid;

	pnfs_get_layout_hdr(lo);
	empty = list_empty(&lo->plh_segs);
	pnfs_clear_layoutcommit(ino, &tmp_list);
	pnfs_mark_matching_lsegs_invalid(lo, &tmp_list, NULL);

	if (NFS_SERVER(ino)->pnfs_curr_ld->return_range) {
		struct pnfs_layout_range range = {
			.iomode		= IOMODE_ANY,
			.offset		= 0,
			.length		= NFS4_MAX_UINT64,
		};
		NFS_SERVER(ino)->pnfs_curr_ld->return_range(lo, &range);
	}


	if (empty) {
		spin_unlock(&ino->i_lock);
		dprintk("NFS: %s no layout segments to return\n", __func__);
		goto out_put_layout_hdr;
	}

	set_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags);
	send = pnfs_prepare_layoutreturn(lo);
	spin_unlock(&ino->i_lock);
	pnfs_free_lseg_list(&tmp_list);
	if (send)
		status = pnfs_send_layoutreturn(lo, stateid, IOMODE_ANY, true);
out_put_layout_hdr:
	pnfs_put_layout_hdr(lo);
out:
	dprintk("<-- %s status: %d\n", __func__, status);
	return status;
}
