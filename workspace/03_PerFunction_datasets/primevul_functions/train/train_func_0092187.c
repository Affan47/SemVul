void CLASS setOlympusBodyFeatures(unsigned long long id)
{
  imgdata.lens.makernotes.CamID = id;
  if (id == 0x5330303638ULL) {
    strcpy (model, "E-M10MarkIII");
  }
  if ((id == 0x4434303430ULL) ||
      (id == 0x4434303431ULL) ||
      ((id & 0x00ffff0000ULL) == 0x0030300000ULL))
  {
    imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_FT;
    if ((id == 0x4434303430ULL) ||
        (id == 0x4434303431ULL) ||
        ((id >= 0x5330303033ULL) && (id <= 0x5330303138ULL)) ||
        (id == 0x5330303233ULL) ||
        (id == 0x5330303239ULL) ||
        (id == 0x5330303330ULL) ||
        (id == 0x5330303333ULL))
    {
      imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_FT;
    }
    else
    {
      imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_mFT;
    }
  }
  else
  {
    imgdata.lens.makernotes.LensMount = imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_FixedLens;
  }
  return;
}
