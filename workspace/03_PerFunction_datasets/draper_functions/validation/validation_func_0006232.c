stpi_color_traditional_init(stp_vars_t *v,
			    stp_image_t *image,
			    size_t steps)
{
  lut_t *lut;
  const char *image_type = stp_get_string_parameter(v, "ImageType");
  const char *color_correction = stp_get_string_parameter(v, "ColorCorrection");
  const channel_depth_t *channel_depth =
    get_channel_depth(stp_get_string_parameter(v, "ChannelBitDepth"));
  size_t total_channel_bits;

  if (steps != 256 && steps != 65536)
    return -1;
  if (!channel_depth)
    return -1;

  lut = allocate_lut();
  lut->input_color_description =
    get_color_description(stp_get_string_parameter(v, "InputImageType"));
  lut->output_color_description =
    get_color_description(stp_get_string_parameter(v, "STPIOutputType"));

  if (!lut->input_color_description || !lut->output_color_description)
    {
      free_lut(lut);
      return -1;
    }

  if (lut->input_color_description->color_id == COLOR_ID_RAW)
    {
      if (stp_verify_parameter(v, "STPIRawChannels", 1) != PARAMETER_OK)
	{
	  free_lut(lut);
	  return -1;
	}
      lut->out_channels = stp_get_int_parameter(v, "STPIRawChannels");
      lut->in_channels = lut->out_channels;
    }
  else
    {
      lut->out_channels = lut->output_color_description->channel_count;
      lut->in_channels = lut->input_color_description->channel_count;
    }

  stp_allocate_component_data(v, "Color", copy_lut, free_lut, lut);
  lut->steps = steps;
  lut->channel_depth = channel_depth->bits;

  if ((!color_correction || strcmp(color_correction, "None") == 0) &&
      image_type && strcmp(image_type, "None") != 0)
    {
      if (strcmp(image_type, "Text") == 0)
	lut->color_correction = get_color_correction("Threshold");
      else
	lut->color_correction = get_color_correction("None");
    }
  else if (color_correction)
    lut->color_correction = get_color_correction(color_correction);
  else
    lut->color_correction = get_color_correction("None");
  if (lut->color_correction->correction == COLOR_CORRECTION_DEFAULT)
    lut->color_correction =
      (get_color_correction_by_tag
       (lut->output_color_description->default_correction));

  stpi_compute_lut(v);

  lut->image_width = stp_image_width(image);
  total_channel_bits = lut->in_channels * lut->channel_depth;
  lut->in_data = stp_malloc(((lut->image_width * total_channel_bits) + 7)/8);
  memset(lut->in_data, 0, ((lut->image_width * total_channel_bits) + 7) / 8);
  return lut->out_channels;
}
