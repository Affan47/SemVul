__lambda86_ (StructureModel* self, GNode* node) {
	gboolean result = FALSE;
	GNode* _tmp0_ = NULL;
	g_return_val_if_fail (node != NULL, FALSE);
	_tmp0_ = node;
	structure_model_insert_node_in_list (self, _tmp0_);
	result = FALSE;
	return result;
}
