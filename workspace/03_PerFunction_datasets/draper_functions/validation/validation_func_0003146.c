tracker_sparql_backend_real_statistics (TrackerSparqlConnection* base, GCancellable* cancellable, GError** error) {
	TrackerSparqlBackend * self;
	TrackerSparqlCursor* result = NULL;
	TrackerSparqlConnection* _tmp0_;
	TrackerSparqlConnection* _tmp2_;
	GCancellable* _tmp3_;
	TrackerSparqlCursor* _tmp4_ = NULL;
	TrackerSparqlCursor* _tmp5_;
	GError * _inner_error_ = NULL;
#line 149 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	self = (TrackerSparqlBackend*) base;
#line 150 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	g_debug ("tracker-backend.vala:150: %s()", "Tracker.Sparql.Backend.statistics");
#line 151 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp0_ = self->priv->bus;
#line 151 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	if (_tmp0_ == NULL) {
#line 2197 "tracker-backend.c"
		GError* _tmp1_;
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
		_tmp1_ = g_error_new_literal (TRACKER_SPARQL_ERROR, TRACKER_SPARQL_ERROR_UNSUPPORTED, "Statistics support not available for direct-only connection");
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
		_inner_error_ = _tmp1_;
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
		if (((_inner_error_->domain == TRACKER_SPARQL_ERROR) || (_inner_error_->domain == G_IO_ERROR)) || (_inner_error_->domain == G_DBUS_ERROR)) {
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_propagate_error (error, _inner_error_);
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			return NULL;
#line 2209 "tracker-backend.c"
		} else {
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_clear_error (&_inner_error_);
#line 152 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			return NULL;
#line 2217 "tracker-backend.c"
		}
	}
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp2_ = self->priv->bus;
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp3_ = cancellable;
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp4_ = tracker_sparql_connection_statistics (_tmp2_, _tmp3_, &_inner_error_);
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp5_ = _tmp4_;
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	if (_inner_error_ != NULL) {
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
		if (((_inner_error_->domain == TRACKER_SPARQL_ERROR) || (_inner_error_->domain == G_IO_ERROR)) || (_inner_error_->domain == G_DBUS_ERROR)) {
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_propagate_error (error, _inner_error_);
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			return NULL;
#line 2236 "tracker-backend.c"
		} else {
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_clear_error (&_inner_error_);
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			return NULL;
#line 2244 "tracker-backend.c"
		}
	}
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	result = _tmp5_;
#line 154 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	return result;
#line 2251 "tracker-backend.c"
}
