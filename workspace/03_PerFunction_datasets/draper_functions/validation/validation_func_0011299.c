contacts_row_group_queue_resize (ContactsRowGroup* self) {
	g_return_if_fail (self != NULL);
	{
		GeeArrayList* _row_list = NULL;
		GeeArrayList* _tmp0_ = NULL;
		GeeArrayList* _tmp1_ = NULL;
		gint _row_size = 0;
		GeeArrayList* _tmp2_ = NULL;
		gint _tmp3_ = 0;
		gint _tmp4_ = 0;
		gint _row_index = 0;
		_tmp0_ = self->priv->rows;
		_tmp1_ = _g_object_ref0 (_tmp0_);
		_row_list = _tmp1_;
		_tmp2_ = _row_list;
		_tmp3_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp2_);
		_tmp4_ = _tmp3_;
		_row_size = _tmp4_;
		_row_index = -1;
		while (TRUE) {
			gint _tmp5_ = 0;
			gint _tmp6_ = 0;
			gint _tmp7_ = 0;
			ContactsRow* row = NULL;
			GeeArrayList* _tmp8_ = NULL;
			gint _tmp9_ = 0;
			gpointer _tmp10_ = NULL;
			ContactsRow* _tmp11_ = NULL;
			gboolean _tmp12_ = FALSE;
			_tmp5_ = _row_index;
			_row_index = _tmp5_ + 1;
			_tmp6_ = _row_index;
			_tmp7_ = _row_size;
			if (!(_tmp6_ < _tmp7_)) {
				break;
			}
			_tmp8_ = _row_list;
			_tmp9_ = _row_index;
			_tmp10_ = gee_abstract_list_get ((GeeAbstractList*) _tmp8_, _tmp9_);
			row = (ContactsRow*) _tmp10_;
			_tmp11_ = row;
			_tmp12_ = gtk_widget_get_visible ((GtkWidget*) _tmp11_);
			if (_tmp12_) {
				ContactsRow* _tmp13_ = NULL;
				_tmp13_ = row;
				gtk_widget_queue_resize ((GtkWidget*) _tmp13_);
			}
		}
		_g_object_unref0 (_row_list);
	}
}
