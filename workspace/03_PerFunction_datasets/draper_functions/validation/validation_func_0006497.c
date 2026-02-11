ldns_radix_new_node(void* data, uint8_t* key, radix_strlen_t len)
{
	ldns_radix_node_t* node = LDNS_MALLOC(ldns_radix_node_t);
	if (!node) {
		return NULL;
	}
	node->data = data;
	node->key = key;
	node->klen = len;
	node->parent = NULL;
	node->parent_index = 0;
	node->len = 0;
	node->offset = 0;
	node->capacity = 0;
	node->array = NULL;
	return node;
}
