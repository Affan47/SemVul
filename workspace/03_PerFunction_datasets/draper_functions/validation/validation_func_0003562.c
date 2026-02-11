gee_array_list_real_set (GeeAbstractList* base, gint index, gconstpointer item) {
	GeeArrayList * self;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gpointer* _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	gint _tmp4_ = 0;
	gconstpointer _tmp5_ = NULL;
	gpointer _tmp6_ = NULL;
	gpointer _tmp7_ = NULL;
	self = (GeeArrayList*) base;
	_tmp0_ = index;
	_vala_assert (_tmp0_ >= 0, "index >= 0");
	_tmp1_ = index;
	_tmp2_ = self->_size;
	_vala_assert (_tmp1_ < _tmp2_, "index < _size");
	_tmp3_ = self->_items;
	_tmp3__length1 = self->_items_length1;
	_tmp4_ = index;
	_tmp5_ = item;
	_tmp6_ = ((_tmp5_ != NULL) && (self->priv->g_dup_func != NULL)) ? self->priv->g_dup_func ((gpointer) _tmp5_) : ((gpointer) _tmp5_);
	((_tmp3_[_tmp4_] == NULL) || (self->priv->g_destroy_func == NULL)) ? NULL : (_tmp3_[_tmp4_] = (self->priv->g_destroy_func (_tmp3_[_tmp4_]), NULL));
	_tmp3_[_tmp4_] = _tmp6_;
	_tmp7_ = _tmp3_[_tmp4_];
}
