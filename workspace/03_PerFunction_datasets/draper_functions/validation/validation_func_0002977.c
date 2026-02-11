ubifs_tnc_next_ent(struct ubifs_info *c,
					   union ubifs_key *key,
					   const struct qstr *nm)
{
	int n, err, type = key_type(c, key);
	struct ubifs_znode *znode;
	struct ubifs_dent_node *dent;
	struct ubifs_zbranch *zbr;
	union ubifs_key *dkey;

	dbg_tnck(key, "%s ", nm->name ? (char *)nm->name : "(lowest)");
	ubifs_assert(is_hash_key(c, key));

	mutex_lock(&c->tnc_mutex);
	err = ubifs_lookup_level0(c, key, &znode, &n);
	if (unlikely(err < 0))
		goto out_unlock;

	if (nm->name) {
		if (err) {

			if (c->replaying)
				err = fallible_resolve_collision(c, key, &znode, &n,
							 nm, 0);
			else
				err = resolve_collision(c, key, &znode, &n, nm);
			dbg_tnc("rc returned %d, znode %p, n %d",
				err, znode, n);
			if (unlikely(err < 0))
				goto out_unlock;
		}


		err = tnc_next(c, &znode, &n);
		if (unlikely(err))
			goto out_unlock;
	} else {


		if (!err) {


			err = tnc_next(c, &znode, &n);
			if (err)
				goto out_unlock;
		}
	}

	zbr = &znode->zbranch[n];
	dent = kmalloc(zbr->len, GFP_NOFS);
	if (unlikely(!dent)) {
		err = -ENOMEM;
		goto out_unlock;
	}


	dkey = &zbr->key;
	if (key_inum(c, dkey) != key_inum(c, key) ||
	    key_type(c, dkey) != type) {
		err = -ENOENT;
		goto out_free;
	}

	err = tnc_read_node_nm(c, zbr, dent);
	if (unlikely(err))
		goto out_free;

	mutex_unlock(&c->tnc_mutex);
	return dent;

out_free:
	kfree(dent);
out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return ERR_PTR(err);
}
