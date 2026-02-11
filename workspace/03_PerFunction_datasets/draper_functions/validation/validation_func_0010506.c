lt_trie_lookup(lt_trie_t  *trie,
	       const char *key)
{
	lt_return_val_if_fail (trie != NULL, NULL);
	lt_return_val_if_fail (key != NULL, NULL);

	if (!trie->root)
		return NULL;

	return lt_trie_node_lookup(trie->root, key);
}
