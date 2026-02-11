rb_hash_delete_key(VALUE hash, VALUE key)
{
    st_data_t ktmp = (st_data_t)key, val;

    if (!RHASH(hash)->ntbl)
        return Qundef;
    if (RHASH(hash)->iter_lev > 0) {
	if (st_delete_safe(RHASH(hash)->ntbl, &ktmp, &val, Qundef)) {
	    FL_SET(hash, HASH_DELETED);
	    return (VALUE)val;
	}
    }
    else if (st_delete(RHASH(hash)->ntbl, &ktmp, &val))
	return (VALUE)val;
    return Qundef;
}
