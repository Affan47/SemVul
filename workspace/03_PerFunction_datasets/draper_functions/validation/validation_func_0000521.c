gst_y4m_encode_setcaps (GstPad * pad, GstCaps * vscaps)
{
  GstY4mEncode *filter;
  GstStructure *structure;
  gboolean res;
  gint w, h;
  guint32 fourcc;
  const GValue *fps, *par, *interlaced;

  filter = GST_Y4M_ENCODE (GST_PAD_PARENT (pad));

  structure = gst_caps_get_structure (vscaps, 0);

  res = gst_structure_get_int (structure, "width", &w);
  res &= gst_structure_get_int (structure, "height", &h);
  res &= ((fps = gst_structure_get_value (structure, "framerate")) != NULL);
  res &= gst_structure_get_fourcc (structure, "format", &fourcc);

  switch (fourcc) {
    case GST_MAKE_FOURCC ('I', '4', '2', '0'):
    case GST_MAKE_FOURCC ('I', 'Y', 'U', 'V'):
      filter->colorspace = "420";
      break;
    case GST_MAKE_FOURCC ('Y', '4', '2', 'B'):
      filter->colorspace = "422";
      break;
    case GST_MAKE_FOURCC ('Y', '4', '1', 'B'):
      filter->colorspace = "411";
      break;
    case GST_MAKE_FOURCC ('Y', '4', '4', '4'):
      filter->colorspace = "444";
      break;
    default:
      res = FALSE;
      break;
  }

  if (!res || w <= 0 || h <= 0 || !GST_VALUE_HOLDS_FRACTION (fps))
    return FALSE;


  interlaced = gst_structure_get_value (structure, "interlaced");


  par = gst_structure_get_value (structure, "pixel-aspect-ratio");

  filter->width = w;
  filter->height = h;
  filter->fps_num = gst_value_get_fraction_numerator (fps);
  filter->fps_den = gst_value_get_fraction_denominator (fps);
  if ((par != NULL) && GST_VALUE_HOLDS_FRACTION (par)) {
    filter->par_num = gst_value_get_fraction_numerator (par);
    filter->par_den = gst_value_get_fraction_denominator (par);
  } else {
    filter->par_num = 0;
    filter->par_den = 0;
  }
  if ((interlaced != NULL) && G_VALUE_HOLDS (interlaced, G_TYPE_BOOLEAN)) {
    filter->interlaced = g_value_get_boolean (interlaced);
  } else {

    filter->interlaced = FALSE;
  }

  return gst_pad_set_caps (filter->srcpad,
      gst_static_pad_template_get_caps (&y4mencode_src_factory));
}
