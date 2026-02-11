boxes_box_config_finalize (GObject* obj) {
	BoxesBoxConfig * self;
#line 3 "/extra-data/checkout/gnome/gnome-boxes/src/box-config.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, BOXES_TYPE_BOX_CONFIG, BoxesBoxConfig);
#line 9 "/extra-data/checkout/gnome/gnome-boxes/src/box-config.vala"
	_g_object_unref0 (self->priv->source);
#line 23 "/extra-data/checkout/gnome/gnome-boxes/src/box-config.vala"
	_g_free0 (self->priv->_group);
#line 44 "/extra-data/checkout/gnome/gnome-boxes/src/box-config.vala"
	self->priv->access_properties = (_vala_BoxesBoxConfigSyncProperty_array_free (self->priv->access_properties, self->priv->access_properties_length1), NULL);
#line 159 "/extra-data/checkout/gnome/gnome-boxes/src/box-config.vala"
	_g_free0 (self->priv->filter_data);
#line 3 "/extra-data/checkout/gnome/gnome-boxes/src/box-config.vala"
	G_OBJECT_CLASS (boxes_box_config_parent_class)->finalize (obj);
#line 2328 "box-config.c"
}
