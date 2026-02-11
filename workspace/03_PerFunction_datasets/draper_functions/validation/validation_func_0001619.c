rhash_info_by_id(unsigned hash_id)
{
	hash_id &= RHASH_ALL_HASHES;

	if(hash_id != (hash_id & -(int)hash_id)) return NULL;

	return rhash_info_table[rhash_ctz(hash_id)].info;
}
