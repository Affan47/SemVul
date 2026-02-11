currency_construct (GType object_type, const gchar* name, const gchar* display_name, const gchar* symbol) {
	Currency * self = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	g_return_val_if_fail (name != NULL, NULL);
	g_return_val_if_fail (display_name != NULL, NULL);
	g_return_val_if_fail (symbol != NULL, NULL);
	self = (Currency*) g_object_new (object_type, NULL);
	_tmp0_ = name;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->_name);
	self->priv->_name = _tmp1_;
	_tmp2_ = display_name;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->priv->_display_name);
	self->priv->_display_name = _tmp3_;
	_tmp4_ = symbol;
	_tmp5_ = g_strdup (_tmp4_);
	_g_free0 (self->priv->_symbol);
	self->priv->_symbol = _tmp5_;
	return self;
}
