void LibRaw::parse_ciff(int offset, int length, int depth)
{

  int tboff, nrecs, c, type, len, save, wbi = -1;
  ushort key[] = {0x410, 0x45f3};
  INT64 fsize = ifp->size();
  if (metadata_blocks++ > LIBRAW_MAX_METADATA_BLOCKS)
    throw LIBRAW_EXCEPTION_IO_CORRUPT;

  fseek(ifp, offset + length - 4, SEEK_SET);
  tboff = get4() + offset;
  fseek(ifp, tboff, SEEK_SET);
  nrecs = get2();
  if (nrecs < 1)
    return;
  if ((nrecs | depth) > 127)
    return;

  if (nrecs * 10 + offset > fsize)
    return;

  while (nrecs--)
  {
    type = get2();
    len = get4();
    INT64 see = offset + get4();
    save = ftell(ifp);


    if ((type != 0x2007) && (type != 0x580b) && (type != 0x501c) &&
        (type != 0x5029) && (type != 0x5813) && (type != 0x5814) &&
        (type != 0x5817) && (type != 0x5834) && (type != 0x580e))
    {

      if (see >= fsize)
      {
        fseek(ifp, save, SEEK_SET);
        continue;
      }
      fseek(ifp, see, SEEK_SET);
      if ((((type >> 8) + 8) | 8) == 0x38)
      {
        parse_ciff(ftell(ifp), len, depth + 1);
      }
    }

    if (type == 0x3004)
    {
      parse_ciff(ftell(ifp), len, depth + 1);
    }
    else if (type == 0x0810)
    {
      fread(artist, 64, 1, ifp);
    }
    else if (type == 0x080a)
    {
      fread(make, 64, 1, ifp);
      fseek(ifp, strbuflen(make) - 63, SEEK_CUR);
      fread(model, 64, 1, ifp);
    }
    else if (type == 0x1810)
    {
      width = get4();
      height = get4();
      pixel_aspect = int_to_float(get4());
      flip = get4();
    }
    else if (type == 0x1835)
    {
      tiff_compress = get4();
    }
    else if (type == 0x2007)
    {
      thumb_offset = see;
      thumb_length = len;
    }
    else if (type == 0x1818)
    {
      shutter = libraw_powf64l(2.0f, -int_to_float((get4(), get4())));
      ilm.CurAp = aperture = libraw_powf64l(2.0f, int_to_float(get4()) / 2);
    }
    else if (type == 0x102a)
    {

      get2();
      iso_speed =
          libraw_powf64l(2.0f, (get2() + get2()) / 32.0f - 5.0f) * 100.0f;
      ilm.CurAp = aperture = _CanonConvertAperture((get2(), get2()));
      shutter = libraw_powf64l(2.0, -((short)get2()) / 32.0);
      wbi = (get2(), get2());
      if (wbi > 17)
        wbi = 0;
      fseek(ifp, 32, SEEK_CUR);
      if (shutter > 1e6)
        shutter = get2() / 10.0;
    }
    else if (type == 0x102c)
    {
      if (get2() > 512)
      {
        fseek(ifp, 118, SEEK_CUR);
        FORC4 cam_mul[c ^ 2] = get2();
      }
      else
      {
        fseek(ifp, 98, SEEK_CUR);
        FORC4 cam_mul[c ^ (c >> 1) ^ 1] = get2();
      }
    }
    else if (type == 0x10a9)
    {

      int bls = 0;
      int table[] = {
          LIBRAW_WBI_Auto,
          LIBRAW_WBI_Daylight,
          LIBRAW_WBI_Cloudy,
          LIBRAW_WBI_Tungsten,
          LIBRAW_WBI_FL_W,
          LIBRAW_WBI_Flash,
          LIBRAW_WBI_Custom,
          LIBRAW_WBI_Auto,
          LIBRAW_WBI_Shade,
          LIBRAW_WBI_Kelvin
      };
      int nWB =
          ((get2() - 2) / 8) -
          1;
      if (nWB)
        FORC4 imgdata.color.WB_Coeffs[LIBRAW_WBI_Auto][c ^ (c >> 1)] = get2();
      if (nWB >= 7)
        Canon_WBpresets(0, 0);
      else
        FORC4 cam_mul[c] = imgdata.color.WB_Coeffs[LIBRAW_WBI_Auto][c];
      if (nWB == 7)
      {

        if ((wbi >= 0) && (wbi < 9) && (wbi != 6))
        {
          FORC4 cam_mul[c] = imgdata.color.WB_Coeffs[wbi][c];
        }
        else
        {
          FORC4 cam_mul[c] = imgdata.color.WB_Coeffs[LIBRAW_WBI_Auto][c];
        }
      }
      else if (nWB == 9)
      {
        FORC4 imgdata.color.WB_Coeffs[LIBRAW_WBI_Custom][c ^ (c >> 1)] = get2();
        FORC4 imgdata.color.WB_Coeffs[LIBRAW_WBI_Kelvin][c ^ (c >> 1)] = get2();
        if ((wbi >= 0) && (wbi < 10))
        {
          FORC4 cam_mul[c] = imgdata.color.WB_Coeffs[wbi][c];
        }
        else
        {
          FORC4 cam_mul[c] = imgdata.color.WB_Coeffs[LIBRAW_WBI_Auto][c];
        }
      }
      FORC4
      bls += (imCanon.ChannelBlackLevel[c ^ (c >> 1)] = get2());
      imCanon.AverageBlackLevel = bls / 4;
    }
    else if (type == 0x102d)
    {
      Canon_CameraSettings(len >> 1);
    }
    else if (type == 0x580b)
    {
      if (strcmp(model, "Canon EOS D30"))
        sprintf(imgdata.shootinginfo.BodySerial, "%d", len);
      else
        sprintf(imgdata.shootinginfo.BodySerial, "%0x-%05d", len >> 16,
                len & 0xffff);
    }
    else if (type == 0x0032)
    {
      if (len == 768)
      {
        fseek(ifp, 72, SEEK_CUR);
        FORC4
        {
          ushort q = get2();
          cam_mul[c ^ (c >> 1)] = 1024.0 / MAX(1, q);
        }
        if (!wbi)
          cam_mul[0] = -1;
      }
      else if (cam_mul[0] <= 0.001f)
      {
        if (get2() == key[0])
          c = (strstr(model, "Pro1") ? "012346000000000000"
                                     : "01345:000000006008")[LIM(0, wbi, 17)] -
              '0' + 2;
        else
        {
          c = "023457000000006000"[LIM(0, wbi, 17)] - '0';
          key[0] = key[1] = 0;
        }
        fseek(ifp, 78 + c * 8, SEEK_CUR);
        FORC4 cam_mul[c ^ (c >> 1) ^ 1] = get2() ^ key[c & 1];
        if (!wbi)
          cam_mul[0] = -1;
      }
    }
    else if (type == 0x1030 && wbi >= 0 && (0x18040 >> wbi & 1))
    {
      ciff_block_1030();
    }
    else if (type == 0x1031)
    {
      raw_width = (get2(), get2());
      raw_height = get2();
    }
    else if (type == 0x501c)
    {
      iso_speed = len & 0xffff;
    }
    else if (type == 0x5029)
    {
      ilm.CurFocal = len >> 16;
      ilm.FocalType = len & 0xffff;
      if (ilm.FocalType == LIBRAW_FT_ZOOM_LENS)
      {
        ilm.FocalUnits = 32;
        if (ilm.FocalUnits > 1)
          ilm.CurFocal /= (float)ilm.FocalUnits;
      }
      focal_len = ilm.CurFocal;
    }
    else if (type == 0x5813)
    {
      flash_used = int_to_float(len);
    }
    else if (type == 0x5814)
    {
      canon_ev = int_to_float(len);
    }
    else if (type == 0x5817)
    {
      shot_order = len;
    }
    else if (type == 0x5834)
    {
      unique_id = ((unsigned long long)len << 32) >> 32;
      setCanonBodyFeatures(unique_id);
    }
    else if (type == 0x580e)
    {
      timestamp = len;
    }
    else if (type == 0x180e)
    {
      timestamp = get4();
    }

#ifdef LOCALTIME
    if ((type | 0x4000) == 0x580e)
      timestamp = mktime(gmtime(&timestamp));
#endif
    fseek(ifp, save, SEEK_SET);
  }
}
