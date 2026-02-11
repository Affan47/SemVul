rsvg_filter_primitive_diffuse_lighting_set_atts (RsvgNode * self, RsvgHandle * ctx,
                                                 RsvgPropertyBag * atts)
{
    const char *value;
    RsvgFilterPrimitiveDiffuseLighting *filter;

    filter = (RsvgFilterPrimitiveDiffuseLighting *) self;


    if (rsvg_property_bag_size (atts)) {
        if ((value = rsvg_property_bag_lookup (atts, "in")))
            g_string_assign (filter->super.in, value);
        if ((value = rsvg_property_bag_lookup (atts, "result")))
            g_string_assign (filter->super.result, value);
        if ((value = rsvg_property_bag_lookup (atts, "x")))
            filter->super.x = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "y")))
            filter->super.y = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "width")))
            filter->super.width = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "height")))
            filter->super.height = _rsvg_css_parse_length (value);
        if ((value = rsvg_property_bag_lookup (atts, "kernelUnitLength")))
            rsvg_css_parse_number_optional_number (value, &filter->dx, &filter->dy);
        if ((value = rsvg_property_bag_lookup (atts, "lighting-color")))
            filter->lightingcolour = rsvg_css_parse_color (value, 0);
        if ((value = rsvg_property_bag_lookup (atts, "diffuseConstant")))
            filter->diffuseConstant = g_ascii_strtod (value, NULL);
        if ((value = rsvg_property_bag_lookup (atts, "surfaceScale")))
            filter->surfaceScale = g_ascii_strtod (value, NULL);
        if ((value = rsvg_property_bag_lookup (atts, "id")))
            rsvg_defs_register_name (ctx->priv->defs, value, &filter->super.super);
    }
}
