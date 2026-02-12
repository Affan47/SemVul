void LibRaw::parse_kodak_ifd(int base)
{
  unsigned entries, tag, type, len, save;
  int j, c, wbi = -1;
  float mul[3] = {1, 1, 1}, num;

  static const int wbtag_kdc[] = {
      LIBRAW_WBI_Auto,
      LIBRAW_WBI_Fluorescent,
      LIBRAW_WBI_Tungsten,
      LIBRAW_WBI_Daylight,
      -1,
      -1,
      LIBRAW_WBI_Shade
  };

  static const int wbtag_dcr[] = {
      LIBRAW_WBI_Daylight,
      LIBRAW_WBI_Tungsten,
      LIBRAW_WBI_Fluorescent,
      LIBRAW_WBI_Flash,
      LIBRAW_WBI_Custom,
      LIBRAW_WBI_Auto
  };


  entries = get2();
  if (entries > 1024)
    return;
  INT64 fsize = ifp->size();
  while (entries--)
  {
    tiff_get(base, &tag, &type, &len, &save);
    INT64 savepos = ftell(ifp);
    if (len > 8 && len + savepos > 2 * fsize)
    {
      fseek(ifp, save, SEEK_SET);
      continue;
    }
    if (callbacks.exif_cb)
    {
      callbacks.exif_cb(callbacks.exifparser_data, tag | 0x20000, type, len,
                        order, ifp, base);
      fseek(ifp, savepos, SEEK_SET);
    }
    if (tag == 0x03eb)
      imgdata.sizes.raw_inset_crop.cleft = get2();
    else if (tag == 0x03ec)
      imgdata.sizes.raw_inset_crop.ctop = get2();
    else if (tag == 0x03ed)
      imgdata.sizes.raw_inset_crop.cwidth = get2();
    else if (tag == 0x03ee)
      imgdata.sizes.raw_inset_crop.cheight = get2();
    else if (tag == 0x03ef)
    {
      if (!strcmp(model, "EOS D2000C"))
        black = get2();
      else
        imKodak.BlackLevelTop = get2();
    }
    else if (tag == 0x03f0)
    {
      if (!strcmp(model, "EOS D2000C"))
      {
        if (black)
          black = (black + get2()) / 2;
        else
          black = get2();
      }
      else
        imKodak.BlackLevelBottom = get2();
    }

    else if (tag == 0x03f1)
    {
      if (len > 0)
      {
        char kti[1024];
        char *pkti;
        int nsym = MIN(len, 1023);
        fread(kti, 1, nsym, ifp);
        kti[nsym] = 0;
#ifdef LIBRAW_WIN32_CALLS
        pkti = strtok(kti, "\x0a");
#else
        char *last = 0;
        pkti = strtok_r(kti, "\x0a", &last);
#endif
        while (pkti != NULL)
        {
          c = 12;
          if ((strlen(pkti) > c) && (!strncasecmp(pkti, "Camera body:", c)))
          {
            while ((pkti[c] == ' ') && (c < strlen(pkti)))
            {
              c++;
            }
            strcpy(ilm.body, pkti + c);
          }
          c = 5;
          if ((strlen(pkti) > c) && (!strncasecmp(pkti, "Lens:", c)))
          {
            ilm.CurFocal = atoi(pkti + c);
          }
          c = 9;
          if ((strlen(pkti) > c) && (!strncasecmp(pkti, "Aperture:", c)))
          {
            while (((pkti[c] == ' ') || (pkti[c] == 'f')) && (c < strlen(pkti)))
            {
              c++;
            }
            ilm.CurAp = atof(pkti + c);
          }
          c = 10;
          if ((strlen(pkti) > c) && (!strncasecmp(pkti, "ISO Speed:", c)))
          {
            iso_speed = atoi(pkti + c);
          }
          c = 13;
          if ((strlen(pkti) > c) && (!strncasecmp(pkti, "Focal Length:", c)))
          {
            ilm.CurFocal = atoi(pkti + c);
          }
          c = 13;
          if ((strlen(pkti) > c) && (!strncasecmp(pkti, "Max Aperture:", c)))
          {
            while (((pkti[c] == ' ') || (pkti[c] == 'f')) && (c < strlen(pkti)))
            {
              c++;
            }
            ilm.MaxAp4CurFocal = atof(pkti + c);
          }
          c = 13;
          if ((strlen(pkti) > c) && (!strncasecmp(pkti, "Min Aperture:", c)))
          {
            while (((pkti[c] == ' ') || (pkti[c] == 'f')) && (c < strlen(pkti)))
            {
              c++;
            }
            ilm.MinAp4CurFocal = atof(pkti + c);
          }
#ifdef LIBRAW_WIN32_CALLS
          pkti = strtok(NULL, "\x0a");
#else
          pkti = strtok_r(NULL, "\x0a", &last);
#endif
        }
      }
    }

    else if (tag == 0x03f3)
      imgdata.makernotes.common.FlashEC = getreal(type);

    else if (tag == 0x03fc)
    {
      wbi = getint(type);
      if ((wbi >= 0) && (wbi < 6) && (wbi != -2))
        wbi = wbtag_dcr[wbi];
    }
    else if (tag == 0x03fd && len == 72)
    {
      fseek(ifp, 40, SEEK_CUR);
      FORC3 cam_mul[c] = 2048.0 / fMAX(1.0f, get2());
      wbi = -2;
    }

    else if ((tag == 0x0406) && (len == 1))
      imgdata.makernotes.common.CameraTemperature = getreal(type);
    else if ((tag == 0x0413) && (len == 1))
      imgdata.makernotes.common.SensorTemperature = getreal(type);
    else if (tag == 0x0848)
      Kodak_DCR_WBtags(LIBRAW_WBI_Daylight, type, wbi);
    else if (tag == 0x0849)
      Kodak_DCR_WBtags(LIBRAW_WBI_Tungsten, type, wbi);
    else if (tag == 0x084a)
      Kodak_DCR_WBtags(LIBRAW_WBI_Fluorescent, type, wbi);
    else if (tag == 0x084b)
      Kodak_DCR_WBtags(LIBRAW_WBI_Flash, type, wbi);
    else if (tag == 0x084c)
      Kodak_DCR_WBtags(LIBRAW_WBI_Custom, type, wbi);
    else if (tag == 0x084d)
    {
      if (wbi == -1)
        wbi = LIBRAW_WBI_Auto;
      Kodak_DCR_WBtags(LIBRAW_WBI_Auto, type, wbi);
    }
    else if (tag == 0x089f)
      imKodak.ISOCalibrationGain = getreal(type);
    else if (tag == 0x0903)
      imKodak.AnalogISO = iso_speed = getreal(type);
    else if (tag == 0x090d)
      linear_table(len);
    else if (tag == 0x09ce)
      stmread(imgdata.shootinginfo.InternalBodySerial, len, ifp);
    else if (tag == 0x0e92)
    {
      imKodak.val018percent = get2();
      imgdata.color.linear_max[0] = imgdata.color.linear_max[1] =
          imgdata.color.linear_max[2] = imgdata.color.linear_max[3] =
              (int)(((float)imKodak.val018percent) / 18.0f * 170.0f);
    }
    else if (tag == 0x0e93)
      imgdata.color.linear_max[0] = imgdata.color.linear_max[1] =
          imgdata.color.linear_max[2] = imgdata.color.linear_max[3] =
              imKodak.val170percent = get2();
    else if (tag == 0x0e94)
      imKodak.val100percent = get2();


    else if (tag == 0xfa00)
      stmread(imgdata.shootinginfo.BodySerial, len, ifp);
    else if (tag == 0xfa0d)
    {
      wbi = fgetc(ifp);
      if ((wbi >= 0) && (wbi < 7))
        wbi = wbtag_kdc[wbi];
    }
    else if (tag == 0xfa13)
      width = getint(type);
    else if (tag == 0xfa14)
      height = (getint(type) + 1) & -2;


    else if (tag == 0xfa18)
    {
      imKodak.offset_left = getint(8);
      if (type != 8)
        imKodak.offset_left += 1;
    }
    else if (tag == 0xfa19)
    {
      imKodak.offset_top = getint(8);
      if (type != 8)
        imKodak.offset_top += 1;
    }

    else if (tag == 0xfa25)
      Kodak_KDC_WBtags(LIBRAW_WBI_Auto, wbi);
    else if (tag == 0xfa27)
      Kodak_KDC_WBtags(LIBRAW_WBI_Tungsten, wbi);
    else if (tag == 0xfa28)
      Kodak_KDC_WBtags(LIBRAW_WBI_Fluorescent, wbi);
    else if (tag == 0xfa29)
      Kodak_KDC_WBtags(LIBRAW_WBI_Daylight, wbi);
    else if (tag == 0xfa2a)
      Kodak_KDC_WBtags(LIBRAW_WBI_Shade, wbi);

    else if (tag == 0xfa31)
      imgdata.sizes.raw_inset_crop.cwidth = get2();
    else if (tag == 0xfa32)
      imgdata.sizes.raw_inset_crop.cheight = get2();
    else if (tag == 0xfa3e)
      imgdata.sizes.raw_inset_crop.cleft = get2();
    else if (tag == 0xfa3f)
      imgdata.sizes.raw_inset_crop.ctop = get2();

    else if (((tag == 0x07e4) || (tag == 0xfb01)) &&
             (len == 9))
    {
      if (KodakIllumMatrix(type, (float *)imKodak.romm_camDaylight))
      {
        romm_coeff(imKodak.romm_camDaylight);
      }
    }
    else if (((tag == 0x07e5) || (tag == 0xfb02)) &&
             (len == 9))
      KodakIllumMatrix(type, (float *)imKodak.romm_camTungsten);
    else if (((tag == 0x07e6) || (tag == 0xfb03)) &&
             (len == 9))
      KodakIllumMatrix(type, (float *)imKodak.romm_camFluorescent);
    else if (((tag == 0x07e7) || (tag == 0xfb04)) &&
             (len == 9))
      KodakIllumMatrix(type, (float *)imKodak.romm_camFlash);
    else if (((tag == 0x07e8) || (tag == 0xfb05)) &&
             (len == 9))
      KodakIllumMatrix(type, (float *)imKodak.romm_camCustom);
    else if (((tag == 0x07e9) || (tag == 0xfb06)) &&
             (len == 9))
      KodakIllumMatrix(type, (float *)imKodak.romm_camAuto);

    fseek(ifp, save, SEEK_SET);
  }
}
