tracker_view_get_model (TrackerView* self) {
	GtkTreeModel* result = NULL;
	TrackerViewDisplay _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_display;
	switch (_tmp0_) {
		case TRACKER_VIEW_DISPLAY_CATEGORIES:
		case TRACKER_VIEW_DISPLAY_FILE_LIST:
		{
			GtkTreeView* v = NULL;
			GtkWidget* _tmp1_ = NULL;
			GtkTreeView* _tmp2_ = NULL;
			GtkTreeView* _tmp3_ = NULL;
			GtkTreeModel* _tmp4_ = NULL;
			GtkTreeModel* _tmp5_ = NULL;
			_tmp1_ = self->priv->view;
			_tmp2_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp1_, GTK_TYPE_TREE_VIEW, GtkTreeView));
			v = _tmp2_;
			_tmp3_ = v;
			_tmp4_ = gtk_tree_view_get_model (_tmp3_);
			_tmp5_ = _g_object_ref0 (_tmp4_);
			result = _tmp5_;
			_g_object_unref0 (v);
			return result;
		}
		case TRACKER_VIEW_DISPLAY_FILE_ICONS:
		{
			GtkIconView* v = NULL;
			GtkWidget* _tmp6_ = NULL;
			GtkIconView* _tmp7_ = NULL;
			GtkIconView* _tmp8_ = NULL;
			GtkTreeModel* _tmp9_ = NULL;
			GtkTreeModel* _tmp10_ = NULL;
			_tmp6_ = self->priv->view;
			_tmp7_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp6_, GTK_TYPE_ICON_VIEW, GtkIconView));
			v = _tmp7_;
			_tmp8_ = v;
			_tmp9_ = gtk_icon_view_get_model (_tmp8_);
			_tmp10_ = _g_object_ref0 (_tmp9_);
			result = _tmp10_;
			_g_object_unref0 (v);
			return result;
		}
		default:
		{
			break;
		}
	}
	result = NULL;
	return result;
}
