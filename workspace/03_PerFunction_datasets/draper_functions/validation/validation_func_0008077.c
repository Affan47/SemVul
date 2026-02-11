unity_category_set_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	UnityCategorySet * self;
	parent_class = G_OBJECT_CLASS (unity_category_set_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, UNITY_TYPE_CATEGORY_SET, UnityCategorySet);
	__g_list_free__g_object_unref0_0 (self->priv->categories);
	self->priv->categories = NULL;
	return obj;
}
