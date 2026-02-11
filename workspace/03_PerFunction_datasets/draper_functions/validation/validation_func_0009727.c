DCM_SetRescaling(DicomStream *dcm,int avoid_scaling)
{


  dcm->rescaling=DCM_RS_NONE;
  dcm->max_value_out=dcm->max_value_in;

  if (dcm->phot_interp == DCM_PI_PALETTE_COLOR)
    {
      if (dcm->max_value_in >= MaxColormapSize)
        {
          dcm->max_value_out=MaxColormapSize-1;
          dcm->rescaling=DCM_RS_PRE;
        }
      return;
    }

  if ((dcm->phot_interp == DCM_PI_MONOCHROME1) ||
      (dcm->phot_interp == DCM_PI_MONOCHROME2))
    {
      if ((dcm->transfer_syntax == DCM_TS_JPEG) ||
          (dcm->transfer_syntax == DCM_TS_JPEG_LS) ||
          (dcm->transfer_syntax == DCM_TS_JPEG_2000))
        {

          if (!avoid_scaling)
            dcm->rescaling=DCM_RS_POST;
        }
#if defined(GRAYSCALE_USES_PALETTE)
      else if (dcm->max_value_in >= MaxColormapSize)
        {
          dcm->max_value_out=MaxColormapSize-1;
          dcm->rescaling=DCM_RS_PRE;
        }
#else
      else if (dcm->max_value_in > MaxRGB)
        {
          dcm->max_value_out=MaxRGB;
          dcm->rescaling=DCM_RS_PRE;
        }
#endif
      else if (!avoid_scaling)
        {
#if !defined(GRAYSCALE_USES_PALETTE)
          dcm->max_value_out=MaxRGB;
#endif
          dcm->rescaling=DCM_RS_POST;
        }
      return;
    }

  if (avoid_scaling || (dcm->max_value_in == MaxRGB))
    return;

  dcm->max_value_out=MaxRGB;
  dcm->rescaling=DCM_RS_PRE;
}
