gg_svg_parse_ellipse (struct gg_svg_document *gg_svg_doc, xmlNodePtr node)
{

    struct gg_svg_ellipse *ellipse;
    struct _xmlAttr *attr;
    double cx = 0.0;
    double cy = 0.0;
    double rx = 0.0;
    double ry = 0.0;

    attr = node->properties;
    while (attr)
      {
	  if (attr->type == XML_ATTRIBUTE_NODE)
	    {
		const char *value = NULL;
		const char *name;
		xmlNodePtr child = attr->children;
		name = (const char *) (attr->name);
		if (child)
		    value = (const char *) (child->content);
		if (child && value)
		  {
		      if (strcmp (name, "cx") == 0)
			  cx = atof (value);
		      if (strcmp (name, "cy") == 0)
			  cy = atof (value);
		      if (strcmp (name, "rx") == 0)
			  rx = atof (value);
		      if (strcmp (name, "ry") == 0)
			  ry = atof (value);
		  }
	    }
	  attr = attr->next;
      }
    ellipse = gg_svg_alloc_ellipse (cx, cy, rx, ry);
    gg_svg_insert_shape (gg_svg_doc, GG_SVG_ELLIPSE, ellipse);
    gg_svg_parse_id (NULL, NULL, gg_svg_doc->current_shape, node->properties);
    gg_svg_parse_style (NULL, gg_svg_doc->current_shape, NULL,
			node->properties);
    gg_svg_parse_transform (NULL, gg_svg_doc->current_shape, NULL, NULL,
			    node->properties);
    gg_svg_parse_clip_path (NULL, gg_svg_doc->current_shape, NULL,
			    node->properties);
}
