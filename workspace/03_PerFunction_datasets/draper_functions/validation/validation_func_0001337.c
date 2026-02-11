abraca_collections_view_on_button_press_event (AbracaCollectionsView* self, GtkWidget* w, GdkEventButton* button) {
	gboolean result = FALSE;
	GtkTreePath* path = NULL;
	gint x = 0;
	gint y = 0;
	GdkEventButton _tmp0_;
	guint _tmp1_;
	GtkMenu* _tmp2_;
	GdkEventButton _tmp3_;
	guint _tmp4_;
	guint32 _tmp5_ = 0U;
	GdkEventButton _tmp6_;
	gdouble _tmp7_;
	GdkEventButton _tmp8_;
	gdouble _tmp9_;
	gint _tmp10_;
	gint _tmp11_;
	GtkTreePath* _tmp12_ = NULL;
	gboolean _tmp13_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (w != NULL, FALSE);
	g_return_val_if_fail (button != NULL, FALSE);
	_tmp0_ = *button;
	_tmp1_ = _tmp0_.button;
	if (_tmp1_ != ((guint) 3)) {
		result = FALSE;
		_gtk_tree_path_free0 (path);
		return result;
	}
	_tmp2_ = self->priv->_collection_menu;
	_tmp3_ = *button;
	_tmp4_ = _tmp3_.button;
	_tmp5_ = gtk_get_current_event_time ();
	gtk_menu_popup (_tmp2_, NULL, NULL, NULL, NULL, _tmp4_, _tmp5_);
	_tmp6_ = *button;
	_tmp7_ = _tmp6_.x;
	x = (gint) _tmp7_;
	_tmp8_ = *button;
	_tmp9_ = _tmp8_.y;
	y = (gint) _tmp9_;
	_tmp10_ = x;
	_tmp11_ = y;
	_tmp13_ = gtk_tree_view_get_path_at_pos ((GtkTreeView*) self, _tmp10_, _tmp11_, &_tmp12_, NULL, NULL, NULL);
	_gtk_tree_path_free0 (path);
	path = _tmp12_;
	if (_tmp13_) {
		GtkTreeSelection* _tmp14_ = NULL;
		GtkTreeSelection* _tmp15_;
		GtkTreeSelection* sel;
		GtkTreeSelection* _tmp16_;
		GtkTreePath* _tmp17_;
		gboolean _tmp18_ = FALSE;
		_tmp14_ = gtk_tree_view_get_selection ((GtkTreeView*) self);
		_tmp15_ = _g_object_ref0 (_tmp14_);
		sel = _tmp15_;
		_tmp16_ = sel;
		_tmp17_ = path;
		_tmp18_ = gtk_tree_selection_path_is_selected (_tmp16_, _tmp17_);
		if (_tmp18_) {
			result = TRUE;
			_g_object_unref0 (sel);
			_gtk_tree_path_free0 (path);
			return result;
		}
		_g_object_unref0 (sel);
	}
	result = FALSE;
	_gtk_tree_path_free0 (path);
	return result;
}
