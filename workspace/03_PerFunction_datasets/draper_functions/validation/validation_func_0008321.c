build_tool_runner_finalize (GObject* obj) {
	BuildToolRunner * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_BUILD_TOOL_RUNNER, BuildToolRunner);
	build_tool_destroy (&self->priv->_tool);
	_g_object_unref0 (self->priv->_on_file);
	_g_object_unref0 (self->priv->_view);
	build_job_destroy (&self->priv->_current_job);
	_g_free0 (self->priv->_current_job_title);
	_g_object_unref0 (self->priv->_current_job_runner);
	self->priv->_job_titles = (g_free (self->priv->_job_titles), NULL);
	self->priv->_job_runners = (_vala_array_free (self->priv->_job_runners, self->priv->_job_runners_length1, (GDestroyNotify) g_object_unref), NULL);
	G_OBJECT_CLASS (build_tool_runner_parent_class)->finalize (obj);
}
