__lambda66_ (BoxesTopbar* self) {
	gint _tmp0_ = 0;
	BoxesApp* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	GtkNotebook* _tmp5_ = NULL;
	gint _tmp6_ = 0;
#line 86 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
	_tmp1_ = boxes_app_app;
#line 86 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
	_tmp2_ = boxes_app_get_selection_mode (_tmp1_);
#line 86 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
	_tmp3_ = _tmp2_;
#line 86 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
	if (_tmp3_) {
#line 87 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
		_tmp0_ = (gint) BOXES_TOPBAR_PAGE_SELECTION;
#line 492 "topbar.c"
	} else {
		GtkNotebook* _tmp4_ = NULL;
#line 87 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
		_tmp4_ = self->notebook;
#line 87 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
		g_object_set (_tmp4_, "page", (gint) BOXES_TOPBAR_PAGE_COLLECTION, NULL);
#line 87 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
		_tmp0_ = (gint) BOXES_TOPBAR_PAGE_COLLECTION;
#line 501 "topbar.c"
	}
#line 86 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
	_tmp5_ = self->notebook;
#line 86 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
	_tmp6_ = _tmp0_;
#line 86 "/extra-data/checkout/gnome/gnome-boxes/src/topbar.vala"
	g_object_set (_tmp5_, "page", _tmp6_, NULL);
#line 509 "topbar.c"
}
