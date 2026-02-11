mi_cacheremove(struct mi_root *cmd, void *param)
{
	str mc_system;
	str attr;
	struct mi_node* node= NULL;

	if(cmd == NULL)
	{
		LM_ERR("NULL command\n");
		return init_mi_tree(404, "NULL command", 12);
	}

	node = cmd->node.kids;
	if(node == NULL)
		return init_mi_tree(404, "Too few arguments", 17);

	mc_system = node->value;
	if(mc_system.s == NULL || mc_system.len== 0)
	{
		LM_ERR( "empty memory cache system parameter\n");
		return init_mi_tree(404, "Empty memory cache id", 21);
	}

	node = node->next;
	if(node == NULL)
		return init_mi_tree(404, "Too few arguments", 17);

	attr = node->value;
	if(attr.s == NULL || attr.len== 0)
	{
		LM_ERR( "empty attribute name parameter\n");
		return init_mi_tree(404, "Empty attribute name", 20);
	}

	node = node->next;
	if(node != NULL)
		return init_mi_tree(404, "Too many parameters", 19);

	if(cache_remove(&mc_system, &attr)< 0)
	{
		LM_ERR("cache_remove command failed\n");
		return init_mi_tree(500, "Cache remove command failed", 27);
	}

	return init_mi_tree(200, "OK", 2);
}
