tracker_bus_fd_cursor_construct (GType object_type, gchar* buffer, gulong buffer_size, gchar** variable_names, int variable_names_length1) {
	TrackerBusFDCursor * self = NULL;
	gchar* _tmp0_;
	gulong _tmp1_;
	gchar** _tmp2_;
	gint _tmp2__length1;
	gchar** _tmp3_;
	gint _tmp3__length1;
	gchar** _tmp4_;
	gint _tmp4__length1;
#line 31 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self = (TrackerBusFDCursor*) tracker_sparql_cursor_construct (object_type);
#line 32 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp0_ = buffer;
#line 32 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self->buffer = _tmp0_;
#line 33 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp1_ = buffer_size;
#line 33 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self->buffer_size = _tmp1_;
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp2_ = variable_names;
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp2__length1 = variable_names_length1;
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp3_ = (_tmp2_ != NULL) ? _vala_array_dup3 (_tmp2_, _tmp2__length1) : ((gpointer) _tmp2_);
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp3__length1 = _tmp2__length1;
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self->variable_names = (_vala_array_free (self->variable_names, self->variable_names_length1, (GDestroyNotify) g_free), NULL);
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self->variable_names = _tmp3_;
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self->variable_names_length1 = _tmp3__length1;
#line 34 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self->_variable_names_size_ = self->variable_names_length1;
#line 35 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp4_ = variable_names;
#line 35 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp4__length1 = variable_names_length1;
#line 35 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self->_n_columns = _tmp4__length1;
#line 31 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	return self;
#line 169 "tracker-bus-fd-cursor.c"
}
