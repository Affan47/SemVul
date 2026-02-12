void LibRaw::setCanonBodyFeatures(unsigned long long id)
{

  ilm.CamID = id;
  if ((id == 0x80000001ULL) ||
      (id == 0x80000174ULL) ||
      (id == 0x80000232ULL) ||
      (id == 0x80000169ULL) ||
      (id == 0x80000281ULL)
  )
  {
    ilm.CameraFormat = LIBRAW_FORMAT_APSH;
    ilm.CameraMount = LIBRAW_MOUNT_Canon_EF;
  }
  else if ((id == 0x80000167ULL) ||
           (id == 0x80000188ULL) ||
           (id == 0x80000215ULL) ||
           (id == 0x80000269ULL) ||
           (id == 0x80000328ULL) ||
           (id == 0x80000324ULL) ||
           (id == 0x80000213ULL) ||
           (id == 0x80000218ULL) ||
           (id == 0x80000285ULL) ||
           (id == 0x80000349ULL) ||
           (id == 0x80000382ULL) ||
           (id == 0x80000401ULL) ||
           (id == 0x80000302ULL) ||
           (id == 0x80000406ULL)

  )
  {
    ilm.CameraFormat = LIBRAW_FORMAT_FF;
    ilm.CameraMount = LIBRAW_MOUNT_Canon_EF;
  }
  else if ((id == 0x80000331ULL) ||
           (id == 0x80000355ULL) ||
           (id == 0x03740000ULL) ||
           (id == 0x03840000ULL) ||
           (id == 0x03940000ULL) ||
           (id == 0x00000412ULL) ||
           (id == 0x04070000ULL) ||
           (id == 0x03980000ULL) ||
           (id == CanonID_EOS_M6_Mark_II)
  )
  {
    ilm.CameraFormat = LIBRAW_FORMAT_APSC;
    ilm.CameraMount = LIBRAW_MOUNT_Canon_EF_M;
  }
  else if ((id == 0x80000424ULL) ||
           (id == 0x80000433ULL)
  )
  {
    ilm.CameraFormat = LIBRAW_FORMAT_FF;
    ilm.CameraMount = LIBRAW_MOUNT_Canon_RF;
  }
  else if ((id == 0x01140000ULL) ||
           (id == 0x01668000ULL) ||
           (id > 0x80000000ULL))
  {
    ilm.CameraFormat = LIBRAW_FORMAT_APSC;
    ilm.CameraMount = LIBRAW_MOUNT_Canon_EF;
  }
}
