glade_widget_set_catalog_defaults (GList * list)
{
  GList *l;
  for (l = list; l && l->data; l = l->next)
    {
      GladeProperty      *prop = l->data;
      GladePropertyClass *klass = glade_property_get_class (prop);
      GParamSpec         *pspec = glade_property_class_get_pspec (klass);

      if (glade_property_equals_value (prop, glade_property_class_get_original_default (klass)) &&
          g_param_values_cmp (pspec,
			      glade_property_class_get_original_default (klass),
			      glade_property_class_get_default (klass)))
        glade_property_reset (prop);
    }
}
