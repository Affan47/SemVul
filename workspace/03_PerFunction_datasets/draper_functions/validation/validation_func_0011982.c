structure_finalize (GObject* obj) {
	Structure * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_STRUCTURE, Structure);
	self->priv->_simple_list_buttons = (_vala_array_free (self->priv->_simple_list_buttons, self->priv->_simple_list_buttons_length1, (GDestroyNotify) g_object_unref), NULL);
	_g_object_unref0 (self->priv->_vpaned);
	_g_object_unref0 (self->priv->_tree_view);
	_g_object_unref0 (self->priv->_document_structure);
	_g_object_unref0 (self->priv->_model);
	_g_object_unref0 (self->priv->_list_view);
	_g_object_unref0 (self->priv->_list_view_sw);
	_g_object_unref0 (self->priv->_list_store);
	G_OBJECT_CLASS (structure_parent_class)->finalize (obj);
}
