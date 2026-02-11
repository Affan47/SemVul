dvb_manager_get_device_group_if_exists (DVBManager* self, guint group_id) {
	DVBDeviceGroup* result = NULL;
	DVBDeviceGroup* _result_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_result_ = NULL;
	{
		GeeHashMap* _tmp0_ = NULL;
		_tmp0_ = self->priv->devices;
		g_rec_mutex_lock (&self->priv->__lock_devices);
		{
			GeeHashMap* _tmp1_ = NULL;
			guint _tmp2_ = 0U;
			gboolean _tmp3_ = FALSE;
			_tmp1_ = self->priv->devices;
			_tmp2_ = group_id;
			_tmp3_ = gee_abstract_map_has_key ((GeeAbstractMap*) _tmp1_, (gpointer) ((guintptr) _tmp2_));
			if (_tmp3_) {
				GeeHashMap* _tmp4_ = NULL;
				guint _tmp5_ = 0U;
				gpointer _tmp6_ = NULL;
				_tmp4_ = self->priv->devices;
				_tmp5_ = group_id;
				_tmp6_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp4_, (gpointer) ((guintptr) _tmp5_));
				_g_object_unref0 (_result_);
				_result_ = (DVBDeviceGroup*) _tmp6_;
			}
		}
		__finally99:
		{
			GeeHashMap* _tmp7_ = NULL;
			_tmp7_ = self->priv->devices;
			g_rec_mutex_unlock (&self->priv->__lock_devices);
		}
		if (_inner_error_ != NULL) {
			_g_object_unref0 (_result_);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	result = _result_;
	return result;
}
