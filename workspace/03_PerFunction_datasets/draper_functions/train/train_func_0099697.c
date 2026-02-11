tdb_store(struct tdb_context *tdb,
			 struct tdb_data key, struct tdb_data dbuf, int flag)
{
	struct hash_info h;
	tdb_off_t off;
	tdb_len_t old_room = 0;
	struct tdb_used_record rec;
	enum TDB_ERROR ecode;

	if (tdb->flags & TDB_VERSION1) {
		if (tdb1_store(tdb, key, dbuf, flag) == -1)
			return tdb->last_error;
		return TDB_SUCCESS;
	}

	off = find_and_lock(tdb, key, F_WRLCK, &h, &rec, NULL);
	if (TDB_OFF_IS_ERR(off)) {
		return tdb->last_error = TDB_OFF_TO_ERR(off);
	}


	if (flag == TDB_INSERT) {
		if (off) {
			ecode = TDB_ERR_EXISTS;
			goto out;
		}
	} else {
		if (off) {
			old_room = rec_data_length(&rec)
				+ rec_extra_padding(&rec);
			if (old_room >= dbuf.dsize) {

				ecode = update_rec_hdr(tdb, off,
						       key.dsize, dbuf.dsize,
						       &rec, h.h);
				if (ecode != TDB_SUCCESS) {
					goto out;
				}
				ecode = update_data(tdb,
						    off + sizeof(rec)
						    + key.dsize, dbuf,
						    old_room - dbuf.dsize);
				if (ecode != TDB_SUCCESS) {
					goto out;
				}
				tdb_unlock_hashes(tdb, h.hlock_start,
						  h.hlock_range, F_WRLCK);
				return tdb->last_error = TDB_SUCCESS;
			}
		} else {
			if (flag == TDB_MODIFY) {


				ecode = TDB_ERR_NOEXIST;
				goto out;
			}
		}
	}


	ecode = replace_data(tdb, &h, key, dbuf, off, old_room, off);
out:
	tdb_unlock_hashes(tdb, h.hlock_start, h.hlock_range, F_WRLCK);
	return tdb->last_error = ecode;
}
