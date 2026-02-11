utils_uri_get_dirname (const gchar* uri) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* dir = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	g_return_val_if_fail (uri != NULL, NULL);
	_tmp0_ = uri;
	g_return_val_if_fail (_tmp0_ != NULL, NULL);
	_tmp1_ = uri;
	_tmp2_ = g_path_get_dirname (_tmp1_);
	dir = _tmp2_;
	_tmp3_ = dir;
	if (g_strcmp0 (_tmp3_, ".") == 0) {
		result = NULL;
		_g_free0 (dir);
		return result;
	}
	_tmp4_ = dir;
	_tmp5_ = utils_replace_home_dir_with_tilde (_tmp4_);
	result = _tmp5_;
	_g_free0 (dir);
	return result;
}
