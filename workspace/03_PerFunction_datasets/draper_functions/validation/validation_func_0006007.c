callback_send_b_layer_destroy(void *user, VNodeID node_id, VLayerID layer_id)
{
	VSNodeBitmap *node;
	unsigned int i, count;
	if((node = (VSNodeBitmap *)vs_get_node(node_id, V_NT_BITMAP)) == NULL)
		return;
	if(layer_id >= node->layer_count || node->layers[layer_id].layer == NULL)
		return;
	if(node->layers[layer_id].layer != NULL)
		free(node->layers[layer_id].layer);
	node->layers[layer_id].layer = NULL;
	node->layers[layer_id].type = 0;
	node->layers[layer_id].name[0] = 0;
	vs_destroy_subscription_list(node->layers[layer_id].subscribers);
	node->layers[layer_id].subscribers = NULL;

	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_b_layer_destroy(node_id, layer_id);
	}
	vs_reset_subscript_session();
}
