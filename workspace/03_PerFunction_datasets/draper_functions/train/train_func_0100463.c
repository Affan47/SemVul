dvb_logging_log_manager_createLogger (DVBLoggingLogManager* self, const gchar* name) {
	DVBLoggingLogger* result = NULL;
	DVBLoggingLogger* l = NULL;
	DVBLoggingLogger* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	GeeHashMap* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = dvb_logging_logger_new ();
	l = _tmp0_;
	_tmp1_ = name;
	dvb_logging_logger_set_name (l, _tmp1_);
	_tmp2_ = self->priv->loggers;
	_tmp3_ = name;
	gee_abstract_map_set ((GeeAbstractMap*) _tmp2_, _tmp3_, l);
	result = l;
	return result;
}
