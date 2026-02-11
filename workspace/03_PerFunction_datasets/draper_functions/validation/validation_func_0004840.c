nilfs_btree_concat_left(struct nilfs_bmap *btree,
				    struct nilfs_btree_path *path,
				    int level, __u64 *keyp, __u64 *ptrp)
{
	struct nilfs_btree_node *node, *left;
	int n, ncblk;

	nilfs_btree_do_delete(btree, path, level, keyp, ptrp);

	node = nilfs_btree_get_nonroot_node(path, level);
	left = nilfs_btree_get_sib_node(path, level);
	ncblk = nilfs_btree_nchildren_per_block(btree);

	n = nilfs_btree_node_get_nchildren(node);

	nilfs_btree_node_move_left(left, node, n, ncblk, ncblk);

	if (!buffer_dirty(path[level].bp_sib_bh))
		mark_buffer_dirty(path[level].bp_sib_bh);

	nilfs_btnode_delete(path[level].bp_bh);
	path[level].bp_bh = path[level].bp_sib_bh;
	path[level].bp_sib_bh = NULL;
	path[level].bp_index += nilfs_btree_node_get_nchildren(left);
}
