bluez_real_set_device_connected (Bluetooth* base, guint id, gboolean connected) {
	Bluez * self;
	Device* device = NULL;
	GHashTable* _tmp0_ = NULL;
	guint _tmp1_ = 0U;
	gconstpointer _tmp2_ = NULL;
	Device* _tmp3_ = NULL;
	gchar* path = NULL;
	GHashTable* _tmp4_ = NULL;
	guint _tmp5_ = 0U;
	gconstpointer _tmp6_ = NULL;
	gchar* _tmp7_ = NULL;
	orgbluezDevice* _tmp8_ = NULL;
	const gchar* _tmp9_ = NULL;
	orgbluezDevice* proxy = NULL;
	orgbluezDevice* _tmp13_ = NULL;
	orgbluezDevice* _tmp14_ = NULL;
	gboolean _tmp15_ = FALSE;
	gboolean _tmp16_ = FALSE;
	orgbluezDevice* _tmp17_ = NULL;
	gboolean _tmp19_ = FALSE;
	gboolean _tmp24_ = FALSE;
	self = (Bluez*) base;
	_tmp0_ = self->priv->id_to_device;
	_tmp1_ = id;
	_tmp2_ = g_hash_table_lookup (_tmp0_, (gpointer) ((guintptr) _tmp1_));
	_tmp3_ = _g_object_ref0 ((Device*) _tmp2_);
	device = _tmp3_;
	_tmp4_ = self->priv->id_to_path;
	_tmp5_ = id;
	_tmp6_ = g_hash_table_lookup (_tmp4_, (gpointer) ((guintptr) _tmp5_));
	_tmp7_ = g_strdup ((const gchar*) _tmp6_);
	path = _tmp7_;
	_tmp9_ = path;
	if (_tmp9_ != NULL) {
		GHashTable* _tmp10_ = NULL;
		const gchar* _tmp11_ = NULL;
		gconstpointer _tmp12_ = NULL;
		_tmp10_ = self->priv->path_to_proxy;
		_tmp11_ = path;
		_tmp12_ = g_hash_table_lookup (_tmp10_, _tmp11_);
		_tmp8_ = (orgbluezDevice*) _tmp12_;
	} else {
		_tmp8_ = NULL;
	}
	_tmp13_ = _tmp8_;
	_tmp14_ = _g_object_ref0 (_tmp13_);
	proxy = _tmp14_;
	_tmp17_ = proxy;
	if (_tmp17_ != NULL) {
		Device* _tmp18_ = NULL;
		_tmp18_ = device;
		_tmp16_ = _tmp18_ != NULL;
	} else {
		_tmp16_ = FALSE;
	}
	_tmp19_ = _tmp16_;
	if (_tmp19_) {
		Device* _tmp20_ = NULL;
		gboolean _tmp21_ = FALSE;
		gboolean _tmp22_ = FALSE;
		gboolean _tmp23_ = FALSE;
		_tmp20_ = device;
		_tmp21_ = device_get_is_connected (_tmp20_);
		_tmp22_ = _tmp21_;
		_tmp23_ = connected;
		_tmp15_ = _tmp22_ != _tmp23_;
	} else {
		_tmp15_ = FALSE;
	}
	_tmp24_ = _tmp15_;
	if (_tmp24_) {
		gboolean _tmp25_ = FALSE;
		_tmp25_ = connected;
		if (_tmp25_) {
			orgbluezDevice* _tmp26_ = NULL;
			_tmp26_ = proxy;
			bluez_device_connect (self, _tmp26_);
		} else {
			orgbluezDevice* _tmp27_ = NULL;
			_tmp27_ = proxy;
			bluez_device_disconnect (self, _tmp27_);
		}
		bluez_update_connected (self);
	}
	_g_object_unref0 (proxy);
	_g_free0 (path);
	_g_object_unref0 (device);
}
