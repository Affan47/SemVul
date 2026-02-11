xps_parse_brush(xps_document *doc, fz_matrix ctm, fz_rect area, char *base_uri, xps_resource *dict, xml_element *node)
{
	if (doc->cookie && doc->cookie->abort)
		return;

	if (!strcmp(xml_tag(node), "ImageBrush"))
		xps_parse_image_brush(doc, ctm, area, base_uri, dict, node);
	else if (!strcmp(xml_tag(node), "VisualBrush"))
		xps_parse_visual_brush(doc, ctm, area, base_uri, dict, node);
	else if (!strcmp(xml_tag(node), "LinearGradientBrush"))
		xps_parse_linear_gradient_brush(doc, ctm, area, base_uri, dict, node);
	else if (!strcmp(xml_tag(node), "RadialGradientBrush"))
		xps_parse_radial_gradient_brush(doc, ctm, area, base_uri, dict, node);
	else
		fz_warn(doc->ctx, "unknown brush tag: %s", xml_tag(node));
}
