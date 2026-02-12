unsigned CLASS setCanonBodyFeatures(unsigned id)
{
    if (id == 0x03740000)
      id = 0x80000374;
    else if (id == 0x03840000)
      id = 0x80000384;
    else if (id == 0x03940000)
      id = 0x80000394;
    else if (id == 0x04070000)
      id = 0x80000407;
    else if (id == 0x03980000)
      id = 0x80000398;

  imgdata.lens.makernotes.CamID = id;
  if ((id == 0x80000001) ||
      (id == 0x80000174) ||
      (id == 0x80000232) ||
      (id == 0x80000169) ||
      (id == 0x80000281)
  )
  {
    imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_APSH;
    imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_Canon_EF;
  }
  else if ((id == 0x80000167) ||
           (id == 0x80000188) ||
           (id == 0x80000215) ||
           (id == 0x80000269) ||
           (id == 0x80000328) ||
           (id == 0x80000324) ||
           (id == 0x80000213) ||
           (id == 0x80000218) ||
           (id == 0x80000285) ||
           (id == 0x80000349) ||
           (id == 0x80000382) ||
           (id == 0x80000401) ||
           (id == 0x80000302)
  )
  {
    imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_FF;
    imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_Canon_EF;
  }
  else if ((id == 0x80000331) ||
           (id == 0x80000355) ||
           (id == 0x80000374) ||
           (id == 0x80000384) ||
           (id == 0x80000394) ||
           (id == 0x80000407) ||
           (id == 0x80000398)
  )
  {
    imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_APSC;
    imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_Canon_EF_M;
  }
  else if ((id == 0x01140000) ||
           (id == 0x01668000) ||
           (id > 0x80000000))
  {
    imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_APSC;
    imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_Canon_EF;
    imgdata.lens.makernotes.LensMount = LIBRAW_MOUNT_Unknown;
  }
  else
  {
    imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_FixedLens;
    imgdata.lens.makernotes.LensMount = LIBRAW_MOUNT_FixedLens;
  }

  return id;
}
