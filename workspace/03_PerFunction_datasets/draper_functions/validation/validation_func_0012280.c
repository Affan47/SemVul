build_command_runner_execute_with_output (BuildCommandRunner* self, GError** error) {
	gint std_out = 0;
	const gchar* _tmp0_ = NULL;
	gchar** _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	GPid _tmp2_ = 0;
	gint _tmp3_ = 0;
	GPid _tmp4_ = 0;
	GPid* _tmp5_ = NULL;
	GPid* _tmp6_ = NULL;
	guint _tmp7_ = 0U;
	gint _tmp8_ = 0;
	GIOChannel* _tmp9_ = NULL;
	GIOChannel* _tmp10_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_working_directory;
	_tmp1_ = self->priv->_command_args;
	_tmp1__length1 = self->priv->_command_args_length1;
	g_spawn_async_with_pipes (_tmp0_, _tmp1_, NULL, G_SPAWN_DO_NOT_REAP_CHILD | G_SPAWN_SEARCH_PATH, _build_command_runner_redirect_stderr_to_stdout_gspawn_child_setup_func, self, &_tmp2_, NULL, &_tmp3_, NULL, &_inner_error_);
	_g_free0 (self->priv->_child_pid);
	_tmp4_ = _tmp2_;
	_tmp5_ = __g_pid_dup0 (&_tmp4_);
	self->priv->_child_pid = _tmp5_;
	std_out = _tmp3_;
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	_tmp6_ = self->priv->_child_pid;
	_tmp7_ = g_child_watch_add_full (G_PRIORITY_DEFAULT_IDLE, *_tmp6_, _build_command_runner_on_exit_gchild_watch_func, g_object_ref (self), g_object_unref);
	self->priv->_child_watch_handler = _tmp7_;
	_tmp8_ = std_out;
	_tmp9_ = g_io_channel_unix_new (_tmp8_);
	_g_io_channel_unref0 (self->priv->_out_channel);
	self->priv->_out_channel = _tmp9_;
	_tmp10_ = self->priv->_out_channel;
	g_io_channel_set_encoding (_tmp10_, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}
