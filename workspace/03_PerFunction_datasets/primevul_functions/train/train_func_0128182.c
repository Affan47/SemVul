void LibRaw::setLeicaBodyFeatures(int LeicaMakernoteSignature)
{
  if (LeicaMakernoteSignature == -3)
  {
    ilm.CameraFormat = LIBRAW_FORMAT_APSH;
    ilm.CameraMount = LIBRAW_MOUNT_Leica_M;
  }
  else if (LeicaMakernoteSignature == -2)
  {
    ilm.CameraFormat = LIBRAW_FORMAT_Leica_DMR;
    if ((model[0] == 'R') || (model[6] == 'R'))
      ilm.CameraMount = LIBRAW_MOUNT_Leica_R;
  }
  else if (LeicaMakernoteSignature == 0)
  {
    ilm.CameraMount = ilm.LensMount = LIBRAW_MOUNT_FixedLens;
    ilm.FocalType = LIBRAW_FT_ZOOM_LENS;
  }
  else if ((LeicaMakernoteSignature == 0x0100) ||
           (LeicaMakernoteSignature == 0x0500) ||
           (LeicaMakernoteSignature == 0x0700) ||
           (LeicaMakernoteSignature == 0x1000))
  {
    ilm.CameraFormat = ilm.LensFormat = LIBRAW_FORMAT_APSC;
    ilm.CameraMount = ilm.LensMount = LIBRAW_MOUNT_FixedLens;
    ilm.FocalType = LIBRAW_FT_PRIME_LENS;
  }
  else if (LeicaMakernoteSignature == 0x0400)
  {
    ilm.CameraFormat = ilm.LensFormat = LIBRAW_FORMAT_APSC;
    ilm.CameraMount = ilm.LensMount = LIBRAW_MOUNT_FixedLens;
    ilm.FocalType = LIBRAW_FT_ZOOM_LENS;
  }
  else if ((LeicaMakernoteSignature == 0x0200) ||
           (LeicaMakernoteSignature ==
            0x02ff) ||

           (LeicaMakernoteSignature == 0x0300))
  {
    if ((model[0] == 'M') || (model[6] == 'M'))
    {
      ilm.CameraFormat = LIBRAW_FORMAT_FF;
      ilm.CameraMount = LIBRAW_MOUNT_Leica_M;
    }
    else if ((model[0] == 'S') || (model[6] == 'S'))
    {
      ilm.CameraFormat = LIBRAW_FORMAT_LeicaS;
      ilm.CameraMount = LIBRAW_MOUNT_Leica_S;
    }
  }
  else if ((LeicaMakernoteSignature == 0x0600) ||
           (LeicaMakernoteSignature == 0x0900) ||
           (LeicaMakernoteSignature == 0x1a00))
  {
    if ((model[0] == 'S') || (model[6] == 'S'))
    {
      ilm.CameraFormat = LIBRAW_FORMAT_FF;
      ilm.CameraMount = LIBRAW_MOUNT_Leica_L;
    }
    else if ((model[0] == 'T') || (model[6] == 'T') || (model[0] == 'C') ||
             (model[6] == 'C'))
    {
      ilm.CameraFormat = LIBRAW_FORMAT_APSC;
      ilm.CameraMount = LIBRAW_MOUNT_Leica_L;
    }
    else if (((model[0] == 'Q') || (model[6] == 'Q')) &&
             ((model[1] == '2') || (model[7] == '2')))
    {
      ilm.CameraFormat = ilm.LensFormat = LIBRAW_FORMAT_FF;
      ilm.CameraMount = ilm.LensMount = LIBRAW_MOUNT_FixedLens;
      ilm.FocalType = LIBRAW_FT_PRIME_LENS;
    }
  }
  else if (LeicaMakernoteSignature == 0x0800)
  {
    ilm.CameraFormat = ilm.LensFormat = LIBRAW_FORMAT_FF;
    ilm.CameraMount = ilm.LensMount = LIBRAW_MOUNT_FixedLens;
    ilm.FocalType = LIBRAW_FT_PRIME_LENS;
  }
}
