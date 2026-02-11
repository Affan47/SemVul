gwa_derive_adaptor_for_type (GType object_type, GWADerivedClassData *data)
{
	GladeWidgetAdaptor *adaptor;
	GType               iter_type, derived_type;
	GType               parent_type = GLADE_TYPE_WIDGET_ADAPTOR;
	gchar              *type_name;
	GTypeInfo adaptor_info =
	{
		sizeof (GladeWidgetAdaptorClass),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) gwa_derived_class_init,
		(GClassFinalizeFunc) NULL,
		data,
		sizeof (GladeWidgetAdaptor),
		0,
		(GInstanceInitFunc) gwa_derived_init,
	};

	for (iter_type = g_type_parent (object_type);
	     iter_type > 0;
	     iter_type = g_type_parent (iter_type))
	{
		if ((adaptor =
		     glade_widget_adaptor_get_by_type (iter_type)) != NULL)
		{
			parent_type = G_TYPE_FROM_INSTANCE (adaptor);
			break;
		}
	}


	type_name    = g_strdup_printf ("Glade%sAdaptor", g_type_name (object_type));
	derived_type = g_type_register_static (parent_type, type_name,
					       &adaptor_info, 0);

	return derived_type;
}
