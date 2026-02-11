ubifs_find_free_space(struct ubifs_info *c, int min_space, int *offs,
			  int squeeze)
{
	const struct ubifs_lprops *lprops;
	int lebs, rsvd_idx_lebs, pick_free = 0, err, lnum, flags;

	dbg_find("min_space %d", min_space);
	ubifs_get_lprops(c);


	spin_lock(&c->space_lock);
	if (c->bi.min_idx_lebs > c->lst.idx_lebs)
		rsvd_idx_lebs = c->bi.min_idx_lebs -  c->lst.idx_lebs;
	else
		rsvd_idx_lebs = 0;
	lebs = c->lst.empty_lebs + c->freeable_cnt + c->idx_gc_cnt -
	       c->lst.taken_empty_lebs;
	if (rsvd_idx_lebs < lebs)


		if (c->lst.empty_lebs - c->lst.taken_empty_lebs > 0) {
			pick_free = 1;


			c->lst.taken_empty_lebs += 1;
		}
	spin_unlock(&c->space_lock);

	lprops = do_find_free_space(c, min_space, pick_free, squeeze);
	if (IS_ERR(lprops)) {
		err = PTR_ERR(lprops);
		goto out;
	}

	lnum = lprops->lnum;
	flags = lprops->flags | LPROPS_TAKEN;

	lprops = ubifs_change_lp(c, lprops, LPROPS_NC, LPROPS_NC, flags, 0);
	if (IS_ERR(lprops)) {
		err = PTR_ERR(lprops);
		goto out;
	}

	if (pick_free) {
		spin_lock(&c->space_lock);
		c->lst.taken_empty_lebs -= 1;
		spin_unlock(&c->space_lock);
	}

	*offs = c->leb_size - lprops->free;
	ubifs_release_lprops(c);

	if (*offs == 0) {


		err = ubifs_leb_unmap(c, lnum);
		if (err)
			return err;
	}

	dbg_find("found LEB %d, free %d", lnum, c->leb_size - *offs);
	ubifs_assert(*offs <= c->leb_size - min_space);
	return lnum;

out:
	if (pick_free) {
		spin_lock(&c->space_lock);
		c->lst.taken_empty_lebs -= 1;
		spin_unlock(&c->space_lock);
	}
	ubifs_release_lprops(c);
	return err;
}
