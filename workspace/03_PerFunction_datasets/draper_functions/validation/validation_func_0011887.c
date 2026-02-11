glade_gtk_widget_write_atk_properties (GladeWidget * widget,
                                       GladeXmlContext * context,
                                       GladeXmlNode * node)
{
  GladeXmlNode *child_node, *object_node;
  GladeProperty *name_prop, *desc_prop;

  name_prop = glade_widget_get_property (widget, "AtkObject::accessible-name");
  desc_prop =
      glade_widget_get_property (widget, "AtkObject::accessible-description");


  if (!glade_property_default (name_prop) ||
      !glade_property_default (desc_prop))
    {
      gchar *atkname = g_strdup_printf ("%s-atkobject", glade_widget_get_name (widget));

      child_node = glade_xml_node_new (context, GLADE_XML_TAG_CHILD);
      glade_xml_node_append_child (node, child_node);

      glade_xml_node_set_property_string (child_node,
                                          GLADE_XML_TAG_INTERNAL_CHILD,
                                          GLADE_TAG_A11Y_INTERNAL_NAME);

      object_node = glade_xml_node_new (context, GLADE_XML_TAG_WIDGET);
      glade_xml_node_append_child (child_node, object_node);

      glade_xml_node_set_property_string (object_node,
                                          GLADE_XML_TAG_CLASS, "AtkObject");

      glade_xml_node_set_property_string (object_node,
                                          GLADE_XML_TAG_ID, atkname);

      if (!glade_property_default (name_prop))
        glade_gtk_widget_write_atk_property (name_prop, context, object_node);
      if (!glade_property_default (desc_prop))
        glade_gtk_widget_write_atk_property (desc_prop, context, object_node);

      g_free (atkname);
    }

}
