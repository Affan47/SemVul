get_pixel_size(bgav_h264_vui_t * v, int * w, int * h)
  {
  if(v->aspect_ratio_info_present_flag)
    {
    if(v->aspect_ratio_idc < 17)
      {
      *w = pixel_aspect[v->aspect_ratio_idc].pixel_width;
      *h = pixel_aspect[v->aspect_ratio_idc].pixel_height;
      }
    else if(v->aspect_ratio_idc == 255)
      {
      *w = v->sar_width;
      *h = v->sar_height;
      }
    else
      {
      *w = 1;
      *h = 1;
      }
    }
  else
    {
    *w = 1;
    *h = 1;
    }
  }
