_llistNewNode (const char *key, void *data)
{
	LNode *node = (LNode*) slapi_ch_malloc (sizeof (LNode));
	if (node == NULL)
		return NULL;

	if (key)
		node->key = slapi_ch_strdup (key);
	else
		node->key = NULL;

	node->data = data;
	node->next = NULL;

	return node;
}
