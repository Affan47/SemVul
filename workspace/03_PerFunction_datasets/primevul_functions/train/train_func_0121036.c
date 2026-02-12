void CLASS setCanonBodyFeatures (unsigned id)
      {
      imgdata.lens.makernotes.CamID = id;
	if (
            (id == 0x80000001) ||
            (id == 0x80000174) ||
            (id == 0x80000232) ||
            (id == 0x80000169) ||
            (id == 0x80000281)
            )
          {
            imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_APSH;
            imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_Canon_EF;
          }
        else
          if (
              (id == 0x80000167) ||
              (id == 0x80000188) ||
              (id == 0x80000215) ||
              (id == 0x80000213) ||
              (id == 0x80000218) ||
              (id == 0x80000285) ||
              (id == 0x80000302) ||
              (id == 0x80000269) ||
              (id == 0x80000324) ||
              (id == 0x80000382) ||
              (id == 0x80000401)
              )
            {
              imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_FF;
              imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_Canon_EF;
            }
          else
            if (
                (id == 0x80000331) ||
                (id == 0x80000355) ||
                (id == 0x80000374)
                )
              {
                imgdata.lens.makernotes.CameraFormat = LIBRAW_FORMAT_APSC;
                imgdata.lens.makernotes.CameraMount = LIBRAW_MOUNT_Canon_EF_M;
              }
            else
              if (
                  (id == 0x01140000) ||
                  (id == 0x01668000) ||
                  (id > 0x80000000)
                  )
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

	return;
      }
