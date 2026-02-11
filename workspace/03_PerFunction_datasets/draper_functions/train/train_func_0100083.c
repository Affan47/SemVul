document_structure_env_data_copy (const DocumentStructureEnvData* self, DocumentStructureEnvData* dest) {
	GtkTreePath* _tmp0_ = NULL;
	GtkTreePath* _tmp1_ = NULL;
	StructType _tmp2_ = 0;
	const gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	_tmp0_ = (*self).path;
	_tmp1_ = _gtk_tree_path_copy0 (_tmp0_);
	_gtk_tree_path_free0 ((*dest).path);
	(*dest).path = _tmp1_;
	_tmp2_ = (*self).type;
	(*dest).type = _tmp2_;
	_tmp3_ = (*self).first_caption;
	_tmp4_ = g_strdup (_tmp3_);
	_g_free0 ((*dest).first_caption);
	(*dest).first_caption = _tmp4_;
}
