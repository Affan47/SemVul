void CLASS parseNikonMakernote (int base, int uptag, unsigned dng_writer)
{
#define imn imgdata.makernotes.nikon
#define ilm imgdata.lens.makernotes
#define icWB imgdata.color.WB_Coeffs

  unsigned offset = 0, entries, tag, type, len, save;

  unsigned c, i;
  uchar *LensData_buf;
  uchar ColorBalanceData_buf[324];
  int ColorBalanceData_ready = 0;
  uchar ci, cj, ck;
  unsigned serial = 0;
  unsigned custom_serial = 0;
  unsigned LensData_len = 0;

  short morder, sorder = order;
  char buf[10];
  INT64 fsize = ifp->size();

  fread(buf, 1, 10, ifp);

  if (!strcmp(buf, "Nikon")) {
    if (buf[6] != '\2') return;
    base = ftell(ifp);
    order = get2();
    if (get2() != 42) goto quit;
    offset = get4();
    fseek(ifp, offset - 8, SEEK_CUR);

  } else {
    fseek(ifp, -10, SEEK_CUR);
  }

  entries = get2();
  if (entries > 1000) return;
  morder = order;

  while (entries--) {
    order = morder;
    tiff_get(base, &tag, &type, &len, &save);
    INT64 pos = ifp->tell();
    if (len > 8 && pos + len > 2 * fsize) {
      fseek(ifp, save, SEEK_SET);
      continue;
    }
    tag |= uptag << 16;
    if (len > 100 * 1024 * 1024)
      goto next;

    if (tag == 0x0002) {
      if (!iso_speed) iso_speed = (get2(), get2());

    } else if (tag == 0x000a) {


      ilm.LensMount = ilm.CameraMount = LIBRAW_MOUNT_FixedLens;
      ilm.FocalType = LIBRAW_FT_ZOOM;

    } else if (tag == 0x000c) {


      cam_mul[0] = getreal(type);
      cam_mul[2] = getreal(type);
      cam_mul[1] = getreal(type);
      cam_mul[3] = getreal(type);

    } else if (tag == 0x11) {
      if (is_raw) {
        fseek(ifp, get4() + base, SEEK_SET);
        parse_tiff_ifd(base);
      }

    } else if (tag == 0x0012) {
      ci = fgetc(ifp);
      cj = fgetc(ifp);
      ck = fgetc(ifp);
      if (ck)
        imgdata.other.FlashEC = (float)(ci * cj) / (float)ck;

    } else if (tag == 0x0014) {
      if (type == 7) {
        if (len == 2560) {
          fseek(ifp, 1248, SEEK_CUR);
          order = 0x4d4d;
          cam_mul[0] = get2() / 256.0;
          cam_mul[2] = get2() / 256.0;
          cam_mul[1] = cam_mul[3] = 1.0;
          icWB[LIBRAW_WBI_Auto][0] = get2();
          icWB[LIBRAW_WBI_Auto][2] = get2();
          icWB[LIBRAW_WBI_Daylight][0] = get2();
          icWB[LIBRAW_WBI_Daylight][2] = get2();
          fseek (ifp, 24, SEEK_CUR);
          icWB[LIBRAW_WBI_Tungsten][0] = get2();
          icWB[LIBRAW_WBI_Tungsten][2] = get2();
          fseek (ifp, 24, SEEK_CUR);
          icWB[LIBRAW_WBI_FL_W][0] = get2();
          icWB[LIBRAW_WBI_FL_W][2] = get2();
          icWB[LIBRAW_WBI_FL_N][0] = get2();
          icWB[LIBRAW_WBI_FL_N][2] = get2();
          icWB[LIBRAW_WBI_FL_D][0] = get2();
          icWB[LIBRAW_WBI_FL_D][2] = get2();
          icWB[LIBRAW_WBI_Cloudy][0] = get2();
          icWB[LIBRAW_WBI_Cloudy][2] = get2();
          fseek (ifp, 24, SEEK_CUR);
          icWB[LIBRAW_WBI_Flash][0] = get2();
          icWB[LIBRAW_WBI_Flash][2] = get2();

          icWB[LIBRAW_WBI_Auto][1] = icWB[LIBRAW_WBI_Auto][3] =
            icWB[LIBRAW_WBI_Daylight][1] = icWB[LIBRAW_WBI_Daylight][3] =
            icWB[LIBRAW_WBI_Tungsten][1] = icWB[LIBRAW_WBI_Tungsten][3] =
            icWB[LIBRAW_WBI_FL_W][1] = icWB[LIBRAW_WBI_FL_W][3] =
            icWB[LIBRAW_WBI_FL_N][1] = icWB[LIBRAW_WBI_FL_N][3] =
            icWB[LIBRAW_WBI_FL_D][1] = icWB[LIBRAW_WBI_FL_D][3] =
            icWB[LIBRAW_WBI_Cloudy][1] = icWB[LIBRAW_WBI_Cloudy][3] =
            icWB[LIBRAW_WBI_Flash][1] = icWB[LIBRAW_WBI_Flash][3] = 256;

          if (strncmp(model, "E8700", 5)) {
            fseek (ifp, 24, SEEK_CUR);
            icWB[LIBRAW_WBI_Shade][0] = get2();
            icWB[LIBRAW_WBI_Shade][2] = get2();
            icWB[LIBRAW_WBI_Shade][1] = icWB[LIBRAW_WBI_Shade][3] = 256;
          }

        } else if (len == 1280) {
          cam_mul[0] = cam_mul[1] = cam_mul[2] = cam_mul[3] = 1.0;

        } else {
          fread(buf, 1, 10, ifp);
          if (!strncmp(buf, "NRW ", 4)) {
            if (!strcmp(buf + 4, "0100")) {
              fseek(ifp, 0x13de, SEEK_CUR);
              cam_mul[0] = get4() << 1;
              cam_mul[1] = get4();
              cam_mul[3] = get4();
              cam_mul[2] = get4() << 1;
              Nikon_NRW_WBtag (LIBRAW_WBI_Daylight, 0);
              Nikon_NRW_WBtag (LIBRAW_WBI_Cloudy, 0);
              fseek(ifp, 16, SEEK_CUR);
              Nikon_NRW_WBtag (LIBRAW_WBI_Tungsten, 0);
              Nikon_NRW_WBtag (LIBRAW_WBI_FL_W, 0);
              Nikon_NRW_WBtag (LIBRAW_WBI_Flash, 0);
              fseek(ifp, 16, SEEK_CUR);
              Nikon_NRW_WBtag (LIBRAW_WBI_Custom, 0);
              Nikon_NRW_WBtag (LIBRAW_WBI_Auto, 0);

            } else {
              fseek(ifp, 0x16, SEEK_CUR);
              black = get2();
              fseek(ifp, 0x16, SEEK_CUR);
              cam_mul[0] = get4() << 1;
              cam_mul[1] = get4();
              cam_mul[3] = get4();
              cam_mul[2] = get4() << 1;
              Nikon_NRW_WBtag (LIBRAW_WBI_Daylight, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_Cloudy, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_Shade, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_Tungsten, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_FL_W, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_FL_N, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_FL_D, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_HT_Mercury, 1);
              fseek(ifp, 20, SEEK_CUR);
              Nikon_NRW_WBtag (LIBRAW_WBI_Custom, 1);
              Nikon_NRW_WBtag (LIBRAW_WBI_Auto, 1);
            }
          }
        }
      }

    } else if (tag == 0x001b) {
      imn.CropFormat = get2();
      FORC(6) imn.CropData[c] = get2();

    } else if (tag == 0x001d) {
      if (len > 0) {
        while ((c = fgetc(ifp)) && (len-- > 0) && (c != EOF)) {
          if ((!custom_serial) && (!isdigit(c))) {
            if ((strbuflen(model) == 3) && (!strcmp(model, "D50"))) {
              custom_serial = 34;
            } else {
              custom_serial = 96;
            }
          }
          serial = serial * 10 + (isdigit(c) ? c - '0' : c % 10);
        }
        if (!imgdata.shootinginfo.BodySerial[0])
          sprintf(imgdata.shootinginfo.BodySerial, "%d", serial);
      }

    } else if (tag == 0x0025) {
      if (!iso_speed || (iso_speed == 65535)) {
        iso_speed = int(100.0 * libraw_powf64l(2.0f, double((uchar)fgetc(ifp)) / 12.0 - 5.0));
      }

    } else if (tag == 0x003b) {
        imn.ME_WB[0] = getreal(type);
        imn.ME_WB[2] = getreal(type);
        imn.ME_WB[1] = getreal(type);
        imn.ME_WB[3] = getreal(type);

    } else if (tag == 0x03d) {
      FORC4 cblack[c ^ c >> 1] = get2();
      i = cblack[3];
      FORC3 if (i > cblack[c]) i = cblack[c];
      FORC4 cblack[c] -= i;
      black += i;

    } else if (tag == 0x0045) {
        imgdata.sizes.raw_crop.cleft = get2();
        imgdata.sizes.raw_crop.ctop = get2();
        imgdata.sizes.raw_crop.cwidth = get2();
        imgdata.sizes.raw_crop.cheight = get2();

    } else if (tag == 0x0082) {
      stmread(ilm.Attachment, len, ifp);

    } else if (tag == 0x0083) {
      imgdata.lens.nikon.NikonLensType = fgetc(ifp);

    } else if (tag == 0x0084) {
      ilm.MinFocal = getreal(type);
      ilm.MaxFocal = getreal(type);
      ilm.MaxAp4MinFocal = getreal(type);
      ilm.MaxAp4MaxFocal = getreal(type);

    } else if (tag == 0x008b) {
      ci = fgetc(ifp);
      cj = fgetc(ifp);
      ck = fgetc(ifp);
      if (ck) {
        imgdata.lens.nikon.NikonLensFStops = ci * cj * (12 / ck);
        ilm.LensFStops = (float)imgdata.lens.nikon.NikonLensFStops / 12.0f;
      }

    } else if ((tag == 0x008c) || (tag == 0x0096)) {
      meta_offset = ftell(ifp);

    } else if (tag == 0x0093) {
      imn.NEFCompression = i = get2();
      if ((i == 7) || (i == 9)) {
        ilm.LensMount = LIBRAW_MOUNT_FixedLens;
        ilm.CameraMount = LIBRAW_MOUNT_FixedLens;
      }

    } else if (tag == 0x0097) {
      FORC4 imn.ColorBalanceVersion = imn.ColorBalanceVersion * 10 + fgetc(ifp) - '0';
      switch (imn.ColorBalanceVersion) {
      case 100:
        fseek(ifp, 68, SEEK_CUR);
        FORC4 cam_mul[(c >> 1) | ((c & 1) << 1)] = get2();
        break;
      case 102:
        fseek(ifp, 6, SEEK_CUR);
        FORC4 cam_mul[c ^ (c >> 1)] = get2();
        break;
      case 103:
        fseek(ifp, 16, SEEK_CUR);
        FORC4 cam_mul[c] = get2();
      }
      if (imn.ColorBalanceVersion >= 200) {
        if (imn.ColorBalanceVersion != 205) {
          fseek(ifp, 280, SEEK_CUR);
        }
        ColorBalanceData_ready = (fread(ColorBalanceData_buf, 324, 1, ifp) == 324);
      }
      if ((imn.ColorBalanceVersion >= 400) &&
          (imn.ColorBalanceVersion <= 405)) {
        ilm.CameraFormat = LIBRAW_FORMAT_1INCH;
        ilm.CameraMount = LIBRAW_MOUNT_Nikon_CX;
      } else if ((imn.ColorBalanceVersion >= 500) &&
                 (imn.ColorBalanceVersion <= 502)) {
        ilm.CameraMount = ilm.LensMount = LIBRAW_MOUNT_FixedLens;
        ilm.FocalType = LIBRAW_FT_ZOOM;
      } else if (imn.ColorBalanceVersion == 601) {
        ilm.CameraFormat = ilm.LensFormat = LIBRAW_FORMAT_APSC;
        ilm.CameraMount = ilm.LensMount = LIBRAW_MOUNT_FixedLens;
        ilm.FocalType = LIBRAW_FT_FIXED;
      } else if (imn.ColorBalanceVersion == 800) {
        ilm.CameraFormat = LIBRAW_FORMAT_FF;
        ilm.CameraMount = LIBRAW_MOUNT_Nikon_Z;
      }

    } else if (tag == 0x0098) {
      FORC4 imn.LensDataVersion = imn.LensDataVersion * 10 + fgetc(ifp) - '0';
      switch (imn.LensDataVersion) {
      case 100:
        LensData_len = 9;
        break;
      case 101:
      case 201:
      case 202:
      case 203:
        LensData_len = 15;
        break;
      case 204:
        LensData_len = 16;
        break;
      case 400:
        LensData_len = 459;
        break;
      case 401:
        LensData_len = 590;
        break;
      case 402:
        LensData_len = 509;
        break;
      case 403:
        LensData_len = 879;
        break;
      }
      if (LensData_len) {
        LensData_buf = (uchar *)malloc(LensData_len);
        fread(LensData_buf, LensData_len, 1, ifp);
      }

    } else if (tag == 0x00a0) {
        stmread(imgdata.shootinginfo.BodySerial, len, ifp);

    } else if (tag == 0x00a7) {
      imn.NikonKey = fgetc(ifp) ^ fgetc(ifp) ^ fgetc(ifp) ^ fgetc(ifp);
      if (custom_serial) {
        ci = xlat[0][custom_serial];
      } else {
        ci = xlat[0][serial & 0xff];
      }
      cj = xlat[1][imn.NikonKey];
      ck = 0x60;
      if (((unsigned)(imn.ColorBalanceVersion - 200) < 18) && ColorBalanceData_ready) {
        for (i = 0; i < 324; i++)
          ColorBalanceData_buf[i] ^= (cj += ci * ck++);
        i = "66666>666;6A;:;555"[imn.ColorBalanceVersion - 200] - '0';
        FORC4 cam_mul[c ^ (c >> 1) ^ (i & 1)] = sget2(ColorBalanceData_buf + (i & -2) + c * 2);
      }
      if (LensData_len) {
        if (imn.LensDataVersion > 200) {
          for (i = 0; i < LensData_len; i++) {
            LensData_buf[i] ^= (cj += ci * ck++);
          }
        }
        processNikonLensData(LensData_buf, LensData_len);
        LensData_len = 0;
        free(LensData_buf);
      }

    } else if (tag == 0x00a8) {
      FORC4 imn.FlashInfoVersion = imn.FlashInfoVersion * 10 + fgetc(ifp) - '0';

    } else if (tag == 0x00b0) {
      get4();
      imn.ExposureMode = get4();
      imn.nMEshots = get4();
      imn.MEgainOn = get4();

    } else if (tag == 0x00b9) {
      imn.AFFineTune = fgetc(ifp);
      imn.AFFineTuneIndex = fgetc(ifp);
      imn.AFFineTuneAdj = (int8_t)fgetc(ifp);

    } else if ((tag == 0x100) && (type == 7 )) {
      thumb_offset = ftell(ifp);
      thumb_length = len;

    } else if (tag == 0x0e01) {
      int loopc = 0;
      int WhiteBalanceAdj_active = 0;
      order = 0x4949;
      fseek(ifp, 22, SEEK_CUR);
      for (offset = 22; offset + 22 < len; offset += 22 + i) {
        if (loopc++ > 1024)
          throw LIBRAW_EXCEPTION_IO_CORRUPT;
        tag = get4();
        fseek(ifp, 14, SEEK_CUR);
        i = get4() - 4;

        if (tag == 0x76a43204) {
          WhiteBalanceAdj_active = fgetc(ifp);

        } else if (tag == 0xbf3c6c20) {
          if (WhiteBalanceAdj_active) {
            cam_mul[0] = getreal(12);
            cam_mul[2] = getreal(12);
            cam_mul[1] = cam_mul[3] = 1.0;
            i -= 16;
          }
          fseek(ifp, i, SEEK_CUR);

        } else if (tag == 0x76a43207) {
          flip = get2();

        } else {
          fseek(ifp, i, SEEK_CUR);
        }
      }

    } else if (tag == 0x0e22) {
      FORC4 imn.NEFBitDepth[c] = get2();
    }
next:
    fseek(ifp, save, SEEK_SET);
  }
quit:
  order = sorder;
#undef icWB
#undef ilm
#undef imn
}
