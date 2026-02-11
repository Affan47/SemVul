gg_resample_transparent_rgba (const gGraphImagePtr img)
{


    int x;
    int y;
    unsigned char *p_in;
    unsigned char *p_out;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    if (img->pixel_format != GG_PIXEL_RGBA)
	return GGRAPH_ERROR;

    for (y = 0; y < img->height; y++)
      {
	  p_in = img->pixels + (y * img->scanline_width);
	  p_out = img->pixels + (y * img->scanline_width);
	  for (x = 0; x < img->width; x++)
	    {
		r = *p_in++;
		g = *p_in++;
		b = *p_in++;
		p_in++;
		if (is_near_transparent (r, g, b, img))
		  {
		      *p_out++ = img->transparent_red;
		      *p_out++ = img->transparent_green;
		      *p_out++ = img->transparent_blue;
		      *p_out++ = 0;
		  }
		else
		    p_out += 4;
	    }
      }
    return GGRAPH_OK;
}
