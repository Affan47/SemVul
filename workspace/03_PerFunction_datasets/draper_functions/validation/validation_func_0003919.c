dm_config_create_node(struct dm_config_tree *cft, const char *key)
{
	struct dm_config_node *cn;

	if (!(cn = _create_node(cft->mem))) {
		log_error("Failed to create config node.");
		return NULL;
	}
	if (!(cn->key = dm_pool_strdup(cft->mem, key))) {
		log_error("Failed to create config node's key.");
		return NULL;
	}
	cn->parent = NULL;
	cn->v = NULL;

	return cn;
}
