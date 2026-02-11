dvb_utils_is_readable_file (GFile* file) {
	gboolean result = FALSE;
	GFileInfo* info = NULL;
	GFileInfo* _tmp6_ = NULL;
	GFileType _tmp7_ = 0;
	GFileInfo* _tmp12_ = NULL;
	gboolean _tmp13_ = FALSE;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (file != NULL, FALSE);
	{
		GFileInfo* _tmp0_ = NULL;
		GFile* _tmp1_ = NULL;
		GFileInfo* _tmp2_ = NULL;
		_tmp1_ = file;
		_tmp2_ = g_file_query_info (_tmp1_, DVB_UTILS_READ_ATTRS, 0, NULL, &_inner_error_);
		_tmp0_ = _tmp2_;
		if (_inner_error_ != NULL) {
			goto __catch202_g_error;
		}
		_g_object_unref0 (info);
		info = _tmp0_;
	}
	goto __finally202;
	__catch202_g_error:
	{
		GError* e = NULL;
		DVBLoggingLogger* _tmp3_ = NULL;
		GError* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp3_ = main_log;
		_tmp4_ = e;
		_tmp5_ = _tmp4_->message;
		dvb_logging_logger_error (_tmp3_, "Utils.vala:163: Could not retrieve attributes: %s", _tmp5_);
		result = FALSE;
		_g_error_free0 (e);
		_g_object_unref0 (info);
		return result;
	}
	__finally202:
	if (_inner_error_ != NULL) {
		_g_object_unref0 (info);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	_tmp6_ = info;
	_tmp7_ = g_file_info_get_file_type (_tmp6_);
	if (_tmp7_ != G_FILE_TYPE_REGULAR) {
		DVBLoggingLogger* _tmp8_ = NULL;
		GFile* _tmp9_ = NULL;
		gchar* _tmp10_ = NULL;
		gchar* _tmp11_ = NULL;
		_tmp8_ = main_log;
		_tmp9_ = file;
		_tmp10_ = g_file_get_path (_tmp9_);
		_tmp11_ = _tmp10_;
		dvb_logging_logger_error (_tmp8_, "Utils.vala:168: %s is not a regular file", _tmp11_);
		_g_free0 (_tmp11_);
		result = FALSE;
		_g_object_unref0 (info);
		return result;
	}
	_tmp12_ = info;
	_tmp13_ = g_file_info_get_attribute_boolean (_tmp12_, G_FILE_ATTRIBUTE_ACCESS_CAN_READ);
	if (!_tmp13_) {
		DVBLoggingLogger* _tmp14_ = NULL;
		GFile* _tmp15_ = NULL;
		gchar* _tmp16_ = NULL;
		gchar* _tmp17_ = NULL;
		_tmp14_ = main_log;
		_tmp15_ = file;
		_tmp16_ = g_file_get_path (_tmp15_);
		_tmp17_ = _tmp16_;
		dvb_logging_logger_error (_tmp14_, "Utils.vala:173: Cannot read %s", _tmp17_);
		_g_free0 (_tmp17_);
		result = FALSE;
		_g_object_unref0 (info);
		return result;
	}
	result = TRUE;
	_g_object_unref0 (info);
	return result;
}
