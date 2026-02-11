set_node_direction(GanvNode* node, void* data)
{
	if (GANV_IS_MODULE(node)) {
		ganv_module_set_direction(GANV_MODULE(node), *(GanvDirection*)data);
	}
}
