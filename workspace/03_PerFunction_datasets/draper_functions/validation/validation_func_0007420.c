midgard_key_config_file_construct (GType object_type, MidgardKeyConfigFileContext* keyctx, const char* path, GError** error) {
	GError * _inner_error_;
	MidgardKeyConfigFile * self;
	GKeyFile* _tmp2_;
	g_return_val_if_fail (keyctx != NULL, NULL);
	g_return_val_if_fail (path != NULL, NULL);
	_inner_error_ = NULL;
	self = (MidgardKeyConfigFile*) midgard_key_config_construct (object_type, (MidgardKeyConfigContext*) keyctx, path);
	if (g_str_has_suffix (path, MIDGARD_CONFIG_EXTENSION)) {
		char* _tmp0_;
		self->priv->file_path = (_tmp0_ = g_build_filename (midgard_key_config_context_get_context_path ((MidgardKeyConfigContext*) keyctx), path, NULL), _g_free0 (self->priv->file_path), _tmp0_);
	} else {
		char* _tmp1_;
		self->priv->file_path = (_tmp1_ = g_build_filename (midgard_key_config_context_get_context_path ((MidgardKeyConfigContext*) keyctx), path, MIDGARD_CONFIG_EXTENSION, NULL), _g_free0 (self->priv->file_path), _tmp1_);
	}
	if (!g_path_is_absolute (self->priv->file_path)) {
		_inner_error_ = g_error_new (KEY_CONFIG_CONTEXT_ERROR, KEY_CONFIG_CONTEXT_ERROR_PATH_IS_NOT_ABSOLUTE, "Absolute paths are not accepted while %s is passed.", self->priv->file_path);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == KEY_CONFIG_CONTEXT_ERROR) {
				g_propagate_error (error, _inner_error_);
				return NULL;
			} else {
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	}
	self->priv->key_file = (_tmp2_ = g_key_file_new (), _g_key_file_free0 (self->priv->key_file), _tmp2_);
	if (g_file_test (self->priv->file_path, G_FILE_TEST_IS_REGULAR)) {
		self->priv->file_exists = TRUE;
		{
			g_key_file_load_from_file (self->priv->key_file, self->priv->file_path, G_KEY_FILE_KEEP_TRANSLATIONS, &_inner_error_);
			if (_inner_error_ != NULL) {
				goto __catch2_g_error;
				goto __finally2;
			}
		}
		goto __finally2;
		__catch2_g_error:
		{
			GError * e;
			e = _inner_error_;
			_inner_error_ = NULL;
			{
				self->priv->file_exists = FALSE;
				_g_error_free0 (e);
			}
		}
		__finally2:
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == KEY_CONFIG_CONTEXT_ERROR) {
				g_propagate_error (error, _inner_error_);
				return NULL;
			} else {
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	}
	return self;
}
