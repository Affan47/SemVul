static int trie_find(struct trie *root, const char *key, match_fn fn,
		     void *baton)
{
	int i;
	int result;
	struct trie *child;

	if (!*key) {

		if (root->value && !root->len)
			return fn(key, root->value, baton);
		else
			return -1;
	}

	for (i = 0; i < root->len; i++) {

		if (key[i] == '/' && key[i+1] == '/') {
			key++;
			continue;
		}
		if (root->contents[i] != key[i])
			return -1;
	}


	key += i;
	if (!*key)

		return fn(key, root->value, baton);


	while (key[0] == '/' && key[1] == '/')
		key++;

	child = root->children[(unsigned char)*key];
	if (child)
		result = trie_find(child, key + 1, fn, baton);
	else
		result = -1;

	if (result >= 0 || (*key != '/' && *key != 0))
		return result;
	if (root->value)
		return fn(key, root->value, baton);
	else
		return -1;
}
