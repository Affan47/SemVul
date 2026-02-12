void LibRaw::setOlympusBodyFeatures(unsigned long long id)
{
  ilm.CamID = id;

  if ((id == 0x4434303430ULL) ||
      (id == 0x4434303431ULL) ||
      ((id & 0x00ffff0000ULL) == 0x0030300000ULL))
  {
    ilm.CameraFormat = LIBRAW_FORMAT_FT;

    if ((id == 0x4434303430ULL) ||
        (id == 0x4434303431ULL) ||
        ((id >= 0x5330303033ULL) && (id <= 0x5330303138ULL)) ||
        (id == 0x5330303233ULL) ||
        (id == 0x5330303239ULL) ||
        (id == 0x5330303330ULL) ||
        (id == 0x5330303333ULL))
    {
      ilm.CameraMount = LIBRAW_MOUNT_FT;
    }
    else
    {
      ilm.CameraMount = LIBRAW_MOUNT_mFT;
    }
  }
  else
  {
    ilm.LensMount = ilm.CameraMount = LIBRAW_MOUNT_FixedLens;
  }
  return;
}
