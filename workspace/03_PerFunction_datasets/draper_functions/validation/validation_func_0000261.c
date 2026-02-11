cc_region_panel_set_property (GObject * object,
			      guint property_id,
			      const GValue * value,
			      GParamSpec * pspec)
{
	CcRegionPanel *self;

	self = CC_REGION_PANEL (object);

	switch (property_id) {
        case PROP_ARGV: {
                gchar **args;

                args = g_value_get_boxed (value);

                if (args && args[0]) {
                        cc_region_panel_set_page (self, args[0]);
                }
                break;
        }
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id,
						   pspec);
	}
}
