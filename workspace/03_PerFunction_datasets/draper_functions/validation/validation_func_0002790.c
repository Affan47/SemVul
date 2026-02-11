dvb_schedule_real_Next (DVBIDBusSchedule* base, guint32 event_id, GError** error) {
	DVBSchedule * self;
	guint32 result = 0U;
	guint32 next_event = 0U;
	GError * _inner_error_ = NULL;
	self = (DVBSchedule*) base;
	next_event = (guint32) 0;
	{
		DVBEventStorage* _tmp0_ = NULL;
		_tmp0_ = self->priv->events;
		g_rec_mutex_lock (&self->priv->__lock_events);
		{
			DVBEventStorage* _tmp1_ = NULL;
			guint32 _tmp2_ = 0U;
			gboolean _tmp3_ = FALSE;
			_tmp1_ = self->priv->events;
			_tmp2_ = event_id;
			_tmp3_ = dvb_event_storage_contains_event_with_id (_tmp1_, (guint) _tmp2_);
			if (_tmp3_) {
				DVBEventElement* element = NULL;
				DVBEventStorage* _tmp4_ = NULL;
				guint32 _tmp5_ = 0U;
				DVBEventElement* _tmp6_ = NULL;
				DVBEventElement* next = NULL;
				DVBEventStorage* _tmp7_ = NULL;
				DVBEventElement* _tmp8_ = NULL;
				DVBEventElement* _tmp9_ = NULL;
				DVBEventElement* _tmp10_ = NULL;
				_tmp4_ = self->priv->events;
				_tmp5_ = event_id;
				_tmp6_ = dvb_event_storage_get_by_id (_tmp4_, (guint) _tmp5_);
				element = _tmp6_;
				_tmp7_ = self->priv->events;
				_tmp8_ = element;
				_tmp9_ = dvb_event_storage_next (_tmp7_, _tmp8_);
				next = _tmp9_;
				_tmp10_ = next;
				if (_tmp10_ != NULL) {
					DVBEventElement* _tmp11_ = NULL;
					guint _tmp12_ = 0U;
					_tmp11_ = next;
					_tmp12_ = _tmp11_->id;
					next_event = (guint32) _tmp12_;
				}
				_g_object_unref0 (next);
				_g_object_unref0 (element);
			} else {
				DVBLoggingLogger* _tmp13_ = NULL;
				guint32 _tmp14_ = 0U;
				_tmp13_ = dvb_schedule_log;
				_tmp14_ = event_id;
				dvb_logging_logger_debug (_tmp13_, "Schedule.vala:395: No event with id %u", (guint) _tmp14_);
			}
		}
		__finally179:
		{
			DVBEventStorage* _tmp15_ = NULL;
			_tmp15_ = self->priv->events;
			g_rec_mutex_unlock (&self->priv->__lock_events);
		}
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_DBUS_ERROR) {
				g_propagate_error (error, _inner_error_);
				return 0U;
			} else {
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return 0U;
			}
		}
	}
	result = next_event;
	return result;
}
