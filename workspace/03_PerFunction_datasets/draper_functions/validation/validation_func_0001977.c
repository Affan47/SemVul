node_alloc(patricia_t* trie, const void *key, const void *value, int32_t msd) {


	patricia_node_t* node = malloc(sizeof(patricia_node_t));
	if(node==NULL) {
		error(1, errno, "error allocating new trie node");
	}

	node->key = trie->key_dupe(key, trie->key_dupe_xtra);
	node->value = value;
	node->msd = msd;

	node->left = NULL;
	node->right = NULL;

	return node;
}
