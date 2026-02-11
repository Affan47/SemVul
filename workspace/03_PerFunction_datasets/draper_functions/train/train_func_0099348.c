c_attrs_has_key (VALUE self, VALUE key)
{
	RbCollection *coll = NULL;
	VALUE tmp;
	int s;

	StringValue (key);

	tmp = rb_iv_get (self, "collection");
	Data_Get_Struct (tmp, RbCollection, coll);

	s = xmmsc_coll_attribute_get (coll->real, StringValuePtr (key), NULL);

	return s ? Qtrue : Qfalse;
}
