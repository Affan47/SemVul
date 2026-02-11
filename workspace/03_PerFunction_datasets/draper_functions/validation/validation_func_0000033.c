TraverseInputSensor(GF_Node *node, void *rs, Bool is_destroy)
{
	ISStack *st = (ISStack*)gf_node_get_private(node);
	M_InputSensor *is = (M_InputSensor *)node;

	if (is_destroy) {
		GF_Scene *scene;
		if (st->registered) IS_Unregister(node, st);
		scene = (GF_Scene*)gf_sg_get_private(gf_node_get_graph(node));
		gf_term_unqueue_node_traverse(scene->root_od->term, node);
		gf_free(st);
	} else {

		if (!st->mo) st->mo = gf_mo_register(node, &is->url, 0, 0);

		if (st->mo && !st->registered) IS_Register(node);
	}
}
