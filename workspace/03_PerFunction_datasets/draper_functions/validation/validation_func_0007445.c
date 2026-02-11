do_insert_tree(struct quota_handle *h, struct dquot *dquot,
			  unsigned int * treeblk, int depth)
{
	dqbuf_t buf;
	int newson = 0, newact = 0;
	__u32 *ref;
	unsigned int newblk;
	int ret = 0;

	log_debug("inserting in tree: treeblk=%u, depth=%d", *treeblk, depth);
	buf = getdqbuf();
	if (!buf)
		return -ENOMEM;

	if (!*treeblk) {
		ret = get_free_dqblk(h);
		if (ret < 0)
			goto out_buf;
		*treeblk = ret;
		memset(buf, 0, QT_BLKSIZE);
		newact = 1;
	} else {
		read_blk(h, *treeblk, buf);
	}

	ref = (__u32 *) buf;
	newblk = ext2fs_le32_to_cpu(ref[get_index(dquot->dq_id, depth)]);
	if (!newblk)
		newson = 1;
	if (depth == QT_TREEDEPTH - 1) {
		if (newblk)
			log_err("Inserting already present quota entry "
				"(block %u).",
				ref[get_index(dquot->dq_id, depth)]);
		newblk = find_free_dqentry(h, dquot, &ret);
	} else {
		ret = do_insert_tree(h, dquot, &newblk, depth + 1);
	}

	if (newson && ret >= 0) {
		ref[get_index(dquot->dq_id, depth)] =
			ext2fs_cpu_to_le32(newblk);
		write_blk(h, *treeblk, buf);
	} else if (newact && ret < 0) {
		put_free_dqblk(h, buf, *treeblk);
	}

out_buf:
	freedqbuf(buf);
	return ret;
}
