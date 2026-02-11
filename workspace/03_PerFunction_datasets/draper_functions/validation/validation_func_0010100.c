dbg_check_tnc(struct ubifs_info *c, int extra)
{
	struct ubifs_znode *znode;
	long clean_cnt = 0, dirty_cnt = 0;
	int err, last;

	if (!dbg_is_chk_index(c))
		return 0;

	ubifs_assert(mutex_is_locked(&c->tnc_mutex));
	if (!c->zroot.znode)
		return 0;

	znode = ubifs_tnc_postorder_first(c->zroot.znode);
	while (1) {
		struct ubifs_znode *prev;
		struct ubifs_zbranch *zbr;

		if (!znode->parent)
			zbr = &c->zroot;
		else
			zbr = &znode->parent->zbranch[znode->iip];

		err = dbg_check_znode(c, zbr);
		if (err)
			return err;

		if (extra) {
			if (ubifs_zn_dirty(znode))
				dirty_cnt += 1;
			else
				clean_cnt += 1;
		}

		prev = znode;
		znode = ubifs_tnc_postorder_next(znode);
		if (!znode)
			break;


		last = prev->child_cnt - 1;
		if (prev->level == 0 && znode->level == 0 && !c->replaying &&
		    !keys_cmp(c, &prev->zbranch[last].key,
			      &znode->zbranch[0].key)) {
			err = dbg_check_key_order(c, &prev->zbranch[last],
						  &znode->zbranch[0]);
			if (err < 0)
				return err;
			if (err) {
				ubifs_msg(c, "first znode");
				ubifs_dump_znode(c, prev);
				ubifs_msg(c, "second znode");
				ubifs_dump_znode(c, znode);
				return -EINVAL;
			}
		}
	}

	if (extra) {
		if (clean_cnt != atomic_long_read(&c->clean_zn_cnt)) {
			ubifs_err(c, "incorrect clean_zn_cnt %ld, calculated %ld",
				  atomic_long_read(&c->clean_zn_cnt),
				  clean_cnt);
			return -EINVAL;
		}
		if (dirty_cnt != atomic_long_read(&c->dirty_zn_cnt)) {
			ubifs_err(c, "incorrect dirty_zn_cnt %ld, calculated %ld",
				  atomic_long_read(&c->dirty_zn_cnt),
				  dirty_cnt);
			return -EINVAL;
		}
	}

	return 0;
}
