currency_manager_add_currency (CurrencyManager* self, const gchar* short_name) {
	Currency* result = NULL;
	GList* _tmp0_ = NULL;
	const gchar* _tmp8_ = NULL;
	Currency* c = NULL;
	const gchar* _tmp9_ = NULL;
	const gchar* _tmp10_ = NULL;
	const gchar* _tmp11_ = NULL;
	Currency* _tmp12_ = NULL;
	Currency* _tmp13_ = NULL;
	Currency* _tmp14_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (short_name != NULL, NULL);
	_tmp0_ = self->priv->currencies;
	{
		GList* c_collection = NULL;
		GList* c_it = NULL;
		c_collection = _tmp0_;
		for (c_it = c_collection; c_it != NULL; c_it = c_it->next) {
			Currency* _tmp1_ = NULL;
			Currency* c = NULL;
			_tmp1_ = _g_object_ref0 ((Currency*) c_it->data);
			c = _tmp1_;
			{
				Currency* _tmp2_ = NULL;
				gchar* _tmp3_ = NULL;
				gchar* _tmp4_ = NULL;
				gchar* _tmp5_ = NULL;
				const gchar* _tmp6_ = NULL;
				gboolean _tmp7_ = FALSE;
				_tmp2_ = c;
				_tmp3_ = currency_get_name (_tmp2_);
				_tmp4_ = _tmp3_;
				_tmp5_ = _tmp4_;
				_tmp6_ = short_name;
				_tmp7_ = g_strcmp0 (_tmp5_, _tmp6_) == 0;
				_g_free0 (_tmp5_);
				if (_tmp7_) {
					result = c;
					return result;
				}
				_g_object_unref0 (c);
			}
		}
	}
	_tmp8_ = short_name;
	g_warning ("currency.vala:133: Currency %s is not in the currency table", _tmp8_);
	_tmp9_ = short_name;
	_tmp10_ = short_name;
	_tmp11_ = short_name;
	_tmp12_ = currency_new (_tmp9_, _tmp10_, _tmp11_);
	c = _tmp12_;
	_tmp13_ = c;
	_tmp14_ = _g_object_ref0 (_tmp13_);
	self->priv->currencies = g_list_append (self->priv->currencies, _tmp14_);
	result = c;
	return result;
}
