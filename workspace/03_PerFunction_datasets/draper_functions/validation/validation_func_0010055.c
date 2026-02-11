__lambda115_ (Block31Data* _data31_) {
	SymbolsView* self;
	GtkTreeIter iter = {0};
	GtkTreeIter _tmp0_ = {0};
	GtkComboBox* _tmp1_ = NULL;
	GtkTreeIter _tmp2_ = {0};
	gboolean _tmp3_ = FALSE;
	GtkListStore* store = NULL;
	SymbolsCategoryType type = 0;
	GtkTreeIter _tmp4_ = {0};
	GtkIconView* _tmp5_ = NULL;
	SymbolsCategoryType _tmp8_ = 0;
	self = _data31_->self;
	iter = _tmp0_;
	_tmp1_ = self->priv->_combo_box;
	_tmp3_ = gtk_combo_box_get_active_iter (_tmp1_, &_tmp2_);
	iter = _tmp2_;
	if (!_tmp3_) {
		return;
	}
	_tmp4_ = iter;
	gtk_tree_model_get (_data31_->categories_model, &_tmp4_, SYMBOLS_CATEGORY_COLUMN_SYMBOLS_STORE, &store, SYMBOLS_CATEGORY_COLUMN_TYPE, &type, -1);
	_tmp5_ = self->priv->_symbol_view;
	if (_tmp5_ != NULL) {
		GtkIconView* _tmp6_ = NULL;
		GtkListStore* _tmp7_ = NULL;
		_tmp6_ = self->priv->_symbol_view;
		_tmp7_ = store;
		gtk_icon_view_set_model (_tmp6_, (GtkTreeModel*) _tmp7_);
	}
	_tmp8_ = type;
	if (_tmp8_ == SYMBOLS_CATEGORY_TYPE_MOST_USED) {
		GtkButton* _tmp9_ = NULL;
		_tmp9_ = self->priv->_clear_button;
		gtk_widget_show ((GtkWidget*) _tmp9_);
	} else {
		GtkButton* _tmp10_ = NULL;
		_tmp10_ = self->priv->_clear_button;
		gtk_widget_hide ((GtkWidget*) _tmp10_);
	}
	_g_object_unref0 (store);
}
