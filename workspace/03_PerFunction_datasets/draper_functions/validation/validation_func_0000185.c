structure_model_reinsert_node (StructureModel* self, GNode* node, gboolean force_first_child) {
	GNode* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	GNode* child = NULL;
	GNode* _tmp2_ = NULL;
	GNode* _tmp3_ = NULL;
	gboolean first_child = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (node != NULL);
	_tmp0_ = node;
	_tmp1_ = force_first_child;
	structure_model_insert_node (self, _tmp0_, _tmp1_);
	_tmp2_ = node;
	_tmp3_ = g_node_first_child (_tmp2_);
	child = _tmp3_;
	first_child = TRUE;
	while (TRUE) {
		GNode* _tmp4_ = NULL;
		GNode* _tmp5_ = NULL;
		gboolean _tmp6_ = FALSE;
		GNode* _tmp7_ = NULL;
		GNode* _tmp8_ = NULL;
		_tmp4_ = child;
		if (!(_tmp4_ != NULL)) {
			break;
		}
		_tmp5_ = child;
		_tmp6_ = first_child;
		structure_model_reinsert_node (self, _tmp5_, _tmp6_);
		_tmp7_ = child;
		_tmp8_ = g_node_next_sibling (_tmp7_);
		child = _tmp8_;
		first_child = FALSE;
	}
}
