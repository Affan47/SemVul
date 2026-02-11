tracker_bus_connection_construct (GType object_type, GError** error) {
	TrackerBusConnection * self = NULL;
	GDBusConnection* _tmp0_ = NULL;
	GDBusConnection* _tmp1_;
	GError* _tmp2_;
	GError* _tmp3_;
	GError * _inner_error_ = NULL;
#line 23 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	self = (TrackerBusConnection*) tracker_sparql_connection_construct (object_type);
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	_tmp0_ = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, &_inner_error_);
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	_tmp1_ = _tmp0_;
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	if (_inner_error_ != NULL) {
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
		if (((_inner_error_->domain == TRACKER_SPARQL_ERROR) || (_inner_error_->domain == G_IO_ERROR)) || (_inner_error_->domain == G_DBUS_ERROR)) {
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
			g_propagate_error (error, _inner_error_);
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
			_g_object_unref0 (self);
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
			return NULL;
#line 563 "tracker-bus.c"
		} else {
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
			g_clear_error (&_inner_error_);
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
			return NULL;
#line 571 "tracker-bus.c"
		}
	}
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	_g_object_unref0 (self->priv->bus);
#line 24 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	self->priv->bus = _tmp1_;
#line 27 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	_tmp2_ = g_error_new_literal (TRACKER_SPARQL_ERROR, TRACKER_SPARQL_ERROR_INTERNAL, "");
#line 27 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	_tmp3_ = _tmp2_;
#line 27 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	_g_error_free0 (_tmp3_);
#line 23 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus.vala"
	return self;
#line 586 "tracker-bus.c"
}
