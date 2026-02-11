__nfs_readpage_from_fscache(struct nfs_open_context *ctx,
				struct inode *inode, struct page *page)
{
	int ret;

	dfprintk(FSCACHE,
		 "NFS: readpage_from_fscache(fsc:%p/p:%p(i:%lx f:%lx)/0x%p)\n",
		 nfs_i_fscache(inode), page, page->index, page->flags, inode);

	ret = fscache_read_or_alloc_page(nfs_i_fscache(inode),
					 page,
					 nfs_readpage_from_fscache_complete,
					 ctx,
					 GFP_KERNEL);

	switch (ret) {
	case 0:
		dfprintk(FSCACHE,
			 "NFS:    readpage_from_fscache: BIO submitted\n");
		nfs_inc_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_OK);
		return ret;

	case -ENOBUFS:
	case -ENODATA:
		nfs_inc_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_FAIL);
		dfprintk(FSCACHE,
			 "NFS:    readpage_from_fscache %d\n", ret);
		return 1;

	default:
		dfprintk(FSCACHE, "NFS:    readpage_from_fscache %d\n", ret);
		nfs_inc_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_READ_FAIL);
	}
	return ret;
}
