wi_dictionary_data_for_key(wi_dictionary_t *dictionary, void *key) {
	_wi_dictionary_bucket_t		*bucket;
	wi_uinteger_t				index;

	index = _WI_DICTIONARY_KEY_HASH(dictionary, key) % dictionary->buckets_count;
	bucket = _wi_dictionary_bucket_for_key(dictionary, key, index);

	if(bucket)
		return bucket->data;

	return NULL;
}
