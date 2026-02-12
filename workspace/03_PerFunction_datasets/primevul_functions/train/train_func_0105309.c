void CLASS setCanonBodyFeatures (unsigned id)
      {
	if (
            (id == 0x80000001) ||
            (id == 0x80000174) ||
            (id == 0x80000232) ||
            (id == 0x80000169) ||
            (id == 0x80000281)
            )
          {
            imgdata.lens.makernotes.CameraFormat = APSH;
            imgdata.lens.makernotes.CameraMount = Canon_EF;
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
              imgdata.lens.makernotes.CameraFormat = FF;
              imgdata.lens.makernotes.CameraMount = Canon_EF;
            }
          else
            if (
                (id == 0x80000331) ||
                (id == 0x80000355)
                )
              {
                imgdata.lens.makernotes.CameraFormat = APSC;
                imgdata.lens.makernotes.CameraMount = Canon_EF_M;
              }
            else
              if (
                  (id == 0x01140000) ||
                  (id == 0x01668000) ||
                  (id > 0x80000000)
                  )
                {
                  imgdata.lens.makernotes.CameraFormat = APSC;
                  imgdata.lens.makernotes.CameraMount = Canon_EF;
                }
              else
                {
                  imgdata.lens.makernotes.CameraMount = FixedLens;
                  imgdata.lens.makernotes.LensMount = FixedLens;
                }

	return;
      }
