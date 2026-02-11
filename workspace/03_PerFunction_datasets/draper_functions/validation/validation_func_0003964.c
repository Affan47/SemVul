xtSplitRoot(struct dinode *ip,
		struct xtree_buf *xroot,
		int64_t offset, int32_t nblocks, int64_t blkno)
{
	xtpage_t *rootpage;
	xtpage_t *newpage;
	int64_t xaddr;
	int32_t nextindex;
	xad_t *xad;
	int rc;
	struct xtree_buf *newbuf;
	int32_t xlen;
	int I_am_logredo = 0;


	rc = alloc_wrksp(sizeof (struct xtree_buf),
			 dynstg_xtreebuf, I_am_logredo, (void **) &newbuf);
	if (rc)
		return (rc);

	newbuf->up = xroot;
	if (xroot->down == NULL) {
		fsim_node_pages = newbuf;
	} else {
		xroot->down->up = newbuf;
	}
	newbuf->down = xroot->down;
	xroot->down = newbuf;
	rc = alloc_wrksp(PSIZE, dynstg_xtreepagebuf, I_am_logredo,
			 (void **) &newpage);
	if (rc)
		return (rc);
	newbuf->page = newpage;


	xlen = 1 << agg_recptr->log2_blksperpg;
	rc = fsck_alloc_fsblks(xlen, &xaddr);
	if (rc)
		return rc;

	rootpage = xroot->page;


	if ((rootpage->header.flag & BT_LEAF) == BT_LEAF) {
		newpage->header.flag = BT_LEAF;
	} else {
		newpage->header.flag = BT_INTERNAL;
	}
	PXDlength(&(newpage->header.self), xlen);
	PXDaddress(&(newpage->header.self), xaddr);
	newpage->header.nextindex = XTENTRYSTART;
	newpage->header.maxentry = XTPAGEMAXSLOT;


	newpage->header.next = 0;
	newpage->header.prev = 0;


	nextindex = rootpage->header.maxentry;
	memcpy(&newpage->xad[XTENTRYSTART], &rootpage->xad[XTENTRYSTART],
	       (nextindex - XTENTRYSTART) << L2XTSLOTSIZE);


	xad = &newpage->xad[nextindex];
	XADoffset(xad, offset);
	XADlength(xad, nblocks);
	XADaddress(xad, blkno);


	newpage->header.nextindex = nextindex + 1;


	xad = &rootpage->xad[XTENTRYSTART];
	XADoffset(xad, 0);
	XADlength(xad, xlen);
	XADaddress(xad, xaddr);


	rootpage->header.flag &= ~BT_LEAF;
	rootpage->header.flag |= BT_INTERNAL;

	rootpage->header.nextindex = XTENTRYSTART + 1;


	ip->di_nblocks += xlen;

	return 0;
}
