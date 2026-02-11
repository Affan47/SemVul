Node_GetExternProtoScene(GF_Node *node)
{
	GF_SceneGraph *sg;
	sg = node->sgprivate->scenegraph;
	if (!sg->pOwningProto) return NULL;
	if (!sg->pOwningProto->proto_interface->ExternProto.count) return NULL;
	sg = sg->pOwningProto->proto_interface->parent_graph;
	while (sg->parent_scene) sg = sg->parent_scene;
	return sg;
}
