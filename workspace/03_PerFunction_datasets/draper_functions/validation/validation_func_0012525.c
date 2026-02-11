build_tool_dialog_open_build_tool (BuildToolDialog* self, BuildTools* build_tools, gint build_tool_num) {
	gboolean result = FALSE;
	BuildTool* build_tool = NULL;
	BuildTools* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	BuildTool* _tmp2_ = NULL;
	BuildTool* _tmp3_ = NULL;
	BuildTools* _tmp4_ = NULL;
	BuildTool* _tmp5_ = NULL;
	BuildTool _tmp6_ = {0};
	gboolean ok = FALSE;
	GtkDialog* _tmp7_ = NULL;
	gint _tmp8_ = 0;
	gboolean _tmp9_ = FALSE;
	GtkDialog* _tmp18_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (build_tools != NULL, FALSE);
	_tmp0_ = build_tools;
	_tmp1_ = build_tool_num;
	_tmp2_ = build_tools_get_build_tool (_tmp0_, _tmp1_);
	build_tool = _tmp2_;
	_tmp3_ = build_tool;
	g_return_val_if_fail (_tmp3_ != NULL, FALSE);
	_tmp4_ = build_tools;
	if (G_TYPE_CHECK_INSTANCE_TYPE (_tmp4_, TYPE_DEFAULT_BUILD_TOOLS)) {
		build_tool_dialog_set_read_only (self);
	} else {
		build_tool_dialog_set_editable (self);
	}
	_tmp5_ = build_tool;
	_tmp6_ = *_tmp5_;
	build_tool_dialog_set_build_tool (self, &_tmp6_);
	_tmp7_ = self->priv->_dialog;
	_tmp8_ = gtk_dialog_run (_tmp7_);
	ok = _tmp8_ == ((gint) GTK_RESPONSE_OK);
	_tmp9_ = ok;
	if (_tmp9_) {
		BuildTool new_build_tool = {0};
		BuildTool _tmp10_ = {0};
		BuildTool* _tmp11_ = NULL;
		gboolean _tmp12_ = FALSE;
		PersonalBuildTools* personal_build_tools = NULL;
		BuildTools* _tmp13_ = NULL;
		PersonalBuildTools* _tmp14_ = NULL;
		PersonalBuildTools* _tmp15_ = NULL;
		gint _tmp16_ = 0;
		BuildTool _tmp17_ = {0};
		build_tool_dialog_retrieve_build_tool (self, &_tmp10_);
		new_build_tool = _tmp10_;
		_tmp11_ = build_tool;
		_tmp12_ = (*_tmp11_).enabled;
		new_build_tool.enabled = _tmp12_;
		_tmp13_ = build_tools;
		_tmp14_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp13_, TYPE_PERSONAL_BUILD_TOOLS) ? ((PersonalBuildTools*) _tmp13_) : NULL);
		personal_build_tools = _tmp14_;
		_tmp15_ = personal_build_tools;
		_tmp16_ = build_tool_num;
		_tmp17_ = new_build_tool;
		personal_build_tools_update (_tmp15_, _tmp16_, &_tmp17_);
		_g_object_unref0 (personal_build_tools);
		build_tool_destroy (&new_build_tool);
	}
	_tmp18_ = self->priv->_dialog;
	gtk_widget_destroy ((GtkWidget*) _tmp18_);
	result = ok;
	_build_tool_free0 (build_tool);
	return result;
}
