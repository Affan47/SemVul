document_structure_clear_all_structure_marks (DocumentStructure* self) {
	g_return_if_fail (self != NULL);
	{
		gint i = 0;
		i = 0;
		{
			gboolean _tmp0_ = FALSE;
			_tmp0_ = TRUE;
			while (TRUE) {
				gint _tmp2_ = 0;
				gint _tmp3_ = 0;
				gchar* mark_name = NULL;
				gint _tmp4_ = 0;
				gchar* _tmp5_ = NULL;
				gchar* _tmp6_ = NULL;
				gchar* _tmp7_ = NULL;
				gchar* _tmp8_ = NULL;
				GtkTextMark* mark = NULL;
				Document* _tmp9_ = NULL;
				const gchar* _tmp10_ = NULL;
				GtkTextMark* _tmp11_ = NULL;
				GtkTextMark* _tmp12_ = NULL;
				GtkTextMark* _tmp13_ = NULL;
				if (!_tmp0_) {
					gint _tmp1_ = 0;
					_tmp1_ = i;
					i = _tmp1_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp2_ = i;
				_tmp3_ = self->priv->_nb_marks;
				if (!(_tmp2_ < _tmp3_)) {
					break;
				}
				_tmp4_ = i;
				_tmp5_ = g_strdup_printf ("%i", _tmp4_);
				_tmp6_ = _tmp5_;
				_tmp7_ = g_strconcat (DOCUMENT_STRUCTURE_MARK_NAME_PREFIX, _tmp6_, NULL);
				_tmp8_ = _tmp7_;
				_g_free0 (_tmp6_);
				mark_name = _tmp8_;
				_tmp9_ = self->priv->_doc;
				_tmp10_ = mark_name;
				_tmp11_ = gtk_text_buffer_get_mark ((GtkTextBuffer*) _tmp9_, _tmp10_);
				_tmp12_ = _g_object_ref0 (_tmp11_);
				mark = _tmp12_;
				_tmp13_ = mark;
				if (_tmp13_ != NULL) {
					Document* _tmp14_ = NULL;
					GtkTextMark* _tmp15_ = NULL;
					_tmp14_ = self->priv->_doc;
					_tmp15_ = mark;
					gtk_text_buffer_delete_mark ((GtkTextBuffer*) _tmp14_, _tmp15_);
				}
				_g_object_unref0 (mark);
				_g_free0 (mark_name);
			}
		}
	}
	self->priv->_nb_marks = 0;
}
