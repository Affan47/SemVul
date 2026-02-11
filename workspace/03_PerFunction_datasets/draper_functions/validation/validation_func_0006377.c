rsvg_pattern_set_atts (RsvgNode * self, RsvgHandle * ctx, RsvgPropertyBag * atts)
{
    RsvgPattern *pattern = (RsvgPattern *) self;
    const char *value;

    if (rsvg_property_bag_size (atts)) {
        if ((value = rsvg_property_bag_lookup (atts, "id")))
            rsvg_defs_register_name (ctx->priv->defs, value, self);
        if ((value = rsvg_property_bag_lookup (atts, "viewBox"))) {
            pattern->vbox = rsvg_css_parse_vbox (value);
            pattern->hasvbox = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "x"))) {
            pattern->x = _rsvg_css_parse_length (value);
            pattern->hasx = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "y"))) {
            pattern->y = _rsvg_css_parse_length (value);
            pattern->hasy = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "width"))) {
            pattern->width = _rsvg_css_parse_length (value);
            pattern->haswidth = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "height"))) {
            pattern->height = _rsvg_css_parse_length (value);
            pattern->hasheight = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "xlink:href"))) {
            if (self != rsvg_defs_lookup (ctx->priv->defs, value)) {


                rsvg_defs_add_resolver (ctx->priv->defs, (RsvgNode **) (void *) &pattern->fallback,
                                        value);
            }
        }
        if ((value = rsvg_property_bag_lookup (atts, "patternTransform"))) {
            rsvg_parse_transform (&pattern->affine, value);
            pattern->hastransform = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "patternUnits"))) {
            if (!strcmp (value, "userSpaceOnUse"))
                pattern->obj_bbox = FALSE;
            else if (!strcmp (value, "objectBoundingBox"))
                pattern->obj_bbox = TRUE;
            pattern->hasbbox = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "patternContentUnits"))) {
            if (!strcmp (value, "userSpaceOnUse"))
                pattern->obj_cbbox = FALSE;
            else if (!strcmp (value, "objectBoundingBox"))
                pattern->obj_cbbox = TRUE;
            pattern->hascbox = TRUE;
        }
        if ((value = rsvg_property_bag_lookup (atts, "preserveAspectRatio"))) {
            pattern->preserve_aspect_ratio = rsvg_css_parse_aspect_ratio (value);
            pattern->hasaspect = TRUE;
        }
    }
}
