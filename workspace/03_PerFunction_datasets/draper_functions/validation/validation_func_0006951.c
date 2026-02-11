rb_hash_keep_if(VALUE hash)
{
    RETURN_ENUMERATOR(hash, 0, 0);
    rb_hash_modify(hash);
    rb_hash_foreach(hash, keep_if_i, hash);
    return hash;
}
