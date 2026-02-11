rb_hash_replace(VALUE hash, VALUE hash2)
{
    rb_hash_modify_check(hash);
    hash2 = to_hash(hash2);
    if (hash == hash2) return hash;
    rb_hash_clear(hash);
    if (RHASH(hash2)->ntbl) {
	rb_hash_tbl(hash);
	RHASH(hash)->ntbl->type = RHASH(hash2)->ntbl->type;
    }
    rb_hash_foreach(hash2, replace_i, hash);
    RHASH_IFNONE(hash) = RHASH_IFNONE(hash2);
    if (FL_TEST(hash2, HASH_PROC_DEFAULT)) {
	FL_SET(hash, HASH_PROC_DEFAULT);
    }
    else {
	FL_UNSET(hash, HASH_PROC_DEFAULT);
    }

    return hash;
}
