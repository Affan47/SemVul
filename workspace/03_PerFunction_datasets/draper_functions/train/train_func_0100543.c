__lambda7_ (Block6Data* _data6_, GIsiCommErrorCode _error_, const gchar* msg) {
	NokiaIsiIsiDeviceGetInformation * self;
	const gchar* _tmp0_ = NULL;
	GIsiCommErrorCode _tmp1_ = 0;
	GHashTable* _tmp3_ = NULL;
	GHashTable* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	GVariant* _tmp7_ = NULL;
	self = _data6_->self;
	_tmp1_ = _error_;
	if (_tmp1_ != GISI_COMM_ERROR_CODE_OK) {
		_tmp0_ = "<unknown>";
	} else {
		const gchar* _tmp2_ = NULL;
		_tmp2_ = msg;
		_tmp0_ = _tmp2_;
	}
	_tmp3_ = fso_gsm_device_get_information_get_info ((FsoGsmDeviceGetInformation*) self);
	_tmp4_ = _tmp3_;
	_tmp5_ = g_strdup ("manufacturer");
	_tmp6_ = _tmp0_;
	_tmp7_ = _variant_new5 (_tmp6_);
	g_hash_table_insert (_tmp4_, _tmp5_, _tmp7_);
	nokia_isi_isi_device_get_information_real_run_co (_data6_->_async_data_);
}
