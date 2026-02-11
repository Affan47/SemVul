tracker_main_sanity_check_option_values (TrackerConfig* config) {
	TrackerConfig* _tmp0_;
	gint _tmp1_;
	gint _tmp2_;
	const gchar* _tmp3_ = NULL;
	gboolean _tmp4_;
	const gchar* _tmp5_;
#line 56 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	g_return_if_fail (config != NULL);
#line 57 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	g_message ("General options:");
#line 58 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp0_ = config;
#line 58 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp1_ = tracker_config_get_verbosity (_tmp0_);
#line 58 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp2_ = _tmp1_;
#line 58 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	g_message ("  Verbosity  ............................  %d", _tmp2_);
#line 60 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	g_message ("Store options:");
#line 61 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp4_ = tracker_main_readonly_mode;
#line 61 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	if (_tmp4_) {
#line 61 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
		_tmp3_ = "yes";
#line 186 "tracker-main.c"
	} else {
#line 61 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
		_tmp3_ = "no";
#line 190 "tracker-main.c"
	}
#line 61 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	_tmp5_ = _tmp3_;
#line 61 "/home/martyn/Source/tracker/src/tracker-store/tracker-main.vala"
	g_message ("  Readonly mode  ........................  %s", _tmp5_);
#line 196 "tracker-main.c"
}
