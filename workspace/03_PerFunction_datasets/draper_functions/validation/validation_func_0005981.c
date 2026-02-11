dvb_channel_list_add (DVBChannelList* self, DVBChannel* channel) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (channel != NULL);
	{
		GeeHashMap* _tmp0_ = NULL;
		_tmp0_ = self->channels;
		g_rec_mutex_lock (&self->priv->__lock_channels);
		{
			GeeHashMap* _tmp1_ = NULL;
			DVBChannel* _tmp2_ = NULL;
			guint _tmp3_ = 0U;
			guint _tmp4_ = 0U;
			DVBChannel* _tmp5_ = NULL;
			_tmp1_ = self->channels;
			_tmp2_ = channel;
			_tmp3_ = dvb_channel_get_Sid (_tmp2_);
			_tmp4_ = _tmp3_;
			_tmp5_ = channel;
			gee_abstract_map_set ((GeeAbstractMap*) _tmp1_, (gpointer) ((guintptr) _tmp4_), _tmp5_);
		}
		__finally34:
		{
			GeeHashMap* _tmp6_ = NULL;
			_tmp6_ = self->channels;
			g_rec_mutex_unlock (&self->priv->__lock_channels);
		}
		if (_inner_error_ != NULL) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}
