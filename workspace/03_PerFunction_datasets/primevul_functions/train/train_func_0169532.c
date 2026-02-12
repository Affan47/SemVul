rsvg_filter_primitive_merge_node_set_atts (RsvgNode *node, gpointer impl, RsvgHandle *handle, RsvgPropertyBag *atts)
{
    RsvgFilterPrimitive *primitive = impl;
    const char *value;


    if ((value = rsvg_property_bag_lookup (atts, "in")))
        g_string_assign (primitive->in, value);
}
