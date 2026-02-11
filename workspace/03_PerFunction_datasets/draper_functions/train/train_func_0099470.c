write_rcvrd_mst_node(struct ubifs_info *c,
				struct ubifs_mst_node *mst)
{
	int err = 0, lnum = UBIFS_MST_LNUM, sz = c->mst_node_alsz;
	__le32 save_flags;

	dbg_rcvry("recovery");

	save_flags = mst->flags;
	mst->flags |= cpu_to_le32(UBIFS_MST_RCVRY);

	ubifs_prepare_node(c, mst, UBIFS_MST_NODE_SZ, 1);
	err = ubifs_leb_change(c, lnum, mst, sz);
	if (err)
		goto out;
	err = ubifs_leb_change(c, lnum + 1, mst, sz);
	if (err)
		goto out;
out:
	mst->flags = save_flags;
	return err;
}
