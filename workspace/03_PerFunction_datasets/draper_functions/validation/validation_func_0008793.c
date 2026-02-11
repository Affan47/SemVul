gal_a11y_e_table_item_get_type (void)
{
	static GType type = 0;

	if (!type) {
		AtkObjectFactory *factory;

		GTypeInfo info = {
			sizeof (GalA11yETableItemClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) eti_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,
			sizeof (GalA11yETableItem),
			0,
			(GInstanceInitFunc) eti_init,
			NULL
		};

		static const GInterfaceInfo atk_component_info = {
			(GInterfaceInitFunc) eti_atk_component_iface_init,
			(GInterfaceFinalizeFunc) NULL,
			NULL
		};
		static const GInterfaceInfo atk_table_info = {
			(GInterfaceInitFunc) eti_atk_table_iface_init,
			(GInterfaceFinalizeFunc) NULL,
			NULL
		};

		static const GInterfaceInfo atk_selection_info = {
			(GInterfaceInitFunc) atk_selection_interface_init,
			(GInterfaceFinalizeFunc) NULL,
			NULL
		};

		factory = atk_registry_get_factory (
			atk_get_default_registry (), GNOME_TYPE_CANVAS_ITEM);
		parent_type = atk_object_factory_get_accessible_type (factory);

		type = gal_a11y_type_register_static_with_private (
			PARENT_TYPE, "GalA11yETableItem", &info, 0,
			sizeof (GalA11yETableItemPrivate), &priv_offset);

		g_type_add_interface_static (type, ATK_TYPE_COMPONENT, &atk_component_info);
		g_type_add_interface_static (type, ATK_TYPE_TABLE, &atk_table_info);
		g_type_add_interface_static (type, ATK_TYPE_SELECTION, &atk_selection_info);
	}

	return type;
}
