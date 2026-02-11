_vala_main (gchar** args, int args_length1) {
	gint result = 0;
	Block1Data* _data1_;
	IBusBus* _tmp0_ = NULL;
	IBusBus* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	IBusBus* _tmp3_ = NULL;
	IBusFactory* factory = NULL;
	IBusBus* _tmp4_ = NULL;
	GDBusConnection* _tmp5_ = NULL;
	IBusFactory* _tmp6_ = NULL;
	IBusFactory* _tmp7_ = NULL;
	guint flags = 0U;
	guint retval = 0U;
	IBusBus* _tmp8_ = NULL;
	guint _tmp9_ = 0U;
	guint32 _tmp10_ = 0U;
	guint _tmp11_ = 0U;
	_data1_ = g_slice_new0 (Block1Data);
	_data1_->_ref_count_ = 1;
	setlocale (LC_ALL, "");
	ibus_init ();
	_tmp0_ = ibus_bus_new ();
	g_object_ref_sink (_tmp0_);
	_data1_->bus = _tmp0_;
	_tmp1_ = _data1_->bus;
	_tmp2_ = ibus_bus_is_connected (_tmp1_);
	if (!_tmp2_) {
		g_warning ("main.vala:34: ibus-daemon does not exist.");
		result = 1;
		block1_data_unref (_data1_);
		_data1_ = NULL;
		return result;
	}
	_tmp3_ = _data1_->bus;
	g_signal_connect (_tmp3_, "disconnected", (GCallback) ___lambda2__ibus_bus_disconnected, NULL);
	_tmp4_ = _data1_->bus;
	_tmp5_ = ibus_bus_get_connection (_tmp4_);
	_tmp6_ = ibus_factory_new (_tmp5_);
	g_object_ref_sink (_tmp6_);
	factory = _tmp6_;
	_data1_->id = 0;
	_tmp7_ = factory;
	g_signal_connect_data (_tmp7_, "create-engine", (GCallback) ___lambda3__ibus_factory_create_engine, block1_data_ref (_data1_), (GClosureNotify) block1_data_unref, 0);
	flags = (guint) (IBUS_BUS_NAME_FLAG_REPLACE_EXISTING | IBUS_BUS_NAME_FLAG_ALLOW_REPLACEMENT);
	_tmp8_ = _data1_->bus;
	_tmp9_ = flags;
	_tmp10_ = ibus_bus_request_name (_tmp8_, "org.freedesktop.IBus.Simple", (guint32) _tmp9_);
	retval = (guint) _tmp10_;
	_tmp11_ = retval;
	if (_tmp11_ == ((guint) 0)) {
		g_warning ("main.vala:79: Registry bus name org.freedesktop.IBus.Simple failed!");
		result = 1;
		_g_object_unref0 (factory);
		block1_data_unref (_data1_);
		_data1_ = NULL;
		return result;
	}
	ibus_main ();
	result = 0;
	_g_object_unref0 (factory);
	block1_data_unref (_data1_);
	_data1_ = NULL;
	return result;
}
