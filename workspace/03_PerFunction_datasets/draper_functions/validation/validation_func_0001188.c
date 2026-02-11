boxes_get_enum_value (const gchar* value_nick, GType enum_type) {
	gint result = 0;
	GEnumClass* enum_class = NULL;
	GType _tmp0_ = 0UL;
	GTypeClass* _tmp1_ = NULL;
	GEnumValue* val = NULL;
	const gchar* _tmp2_ = NULL;
	GEnumValue* _tmp3_ = NULL;
	GEnumValue* _tmp4_ = NULL;
	gint _tmp5_ = 0;
#line 254 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	g_return_val_if_fail (value_nick != NULL, 0);
#line 255 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_tmp0_ = enum_type;
#line 255 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_tmp1_ = g_type_class_ref (_tmp0_);
#line 255 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	enum_class = (GEnumClass*) _tmp1_;
#line 256 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_tmp2_ = value_nick;
#line 256 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_tmp3_ = g_enum_get_value_by_nick (enum_class, _tmp2_);
#line 256 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_tmp4_ = __g_enum_value_dup0 (_tmp3_);
#line 256 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	val = _tmp4_;
#line 257 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	g_return_val_if_fail (val != NULL, -1);
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_tmp5_ = (*val).value;
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	result = _tmp5_;
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_g_free0 (val);
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	_g_type_class_unref0 (enum_class);
#line 259 "/extra-data/checkout/gnome/gnome-boxes/src/util.vala"
	return result;
#line 2739 "util.c"
}
