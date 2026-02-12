void CLASS processCanonCameraInfo(unsigned id, uchar *CameraInfo, unsigned maxlen, unsigned type)
{
  ushort iCanonLensID = 0, iCanonMaxFocal = 0, iCanonMinFocal = 0, iCanonLens = 0, iCanonCurFocal = 0,
         iCanonFocalType = 0;
  if(maxlen<16) return;
  CameraInfo[0] = 0;
  CameraInfo[1] = 0;
  if (type == 4) {
    if ((maxlen == 94)  ||
        (maxlen == 138) ||
        (maxlen == 148) ||
        (maxlen == 156) ||
        (maxlen == 162) ||
        (maxlen == 167) ||
        (maxlen == 171) ||
        (maxlen == 264) ||
        (maxlen > 400))
         imgdata.other.CameraTemperature = sget4(CameraInfo + ((maxlen-3)<<2));
      else if (maxlen == 72) imgdata.other.CameraTemperature = sget4(CameraInfo + ((maxlen-1)<<2));
      else if ((maxlen == 85) || (maxlen == 93)) imgdata.other.CameraTemperature = sget4(CameraInfo + ((maxlen-2)<<2));
      else if ((maxlen == 96) || (maxlen == 104)) imgdata.other.CameraTemperature = sget4(CameraInfo + ((maxlen-4)<<2));
  }

  switch (id)
  {
  case 0x80000001:
  case 0x80000167:
    iCanonCurFocal = 10;
    iCanonLensID = 13;
    iCanonMinFocal = 14;
    iCanonMaxFocal = 16;
    if (!imgdata.lens.makernotes.CurFocal)
      imgdata.lens.makernotes.CurFocal = sget2(CameraInfo + iCanonCurFocal);
    if (!imgdata.lens.makernotes.MinFocal)
      imgdata.lens.makernotes.MinFocal = sget2(CameraInfo + iCanonMinFocal);
    if (!imgdata.lens.makernotes.MaxFocal)
      imgdata.lens.makernotes.MaxFocal = sget2(CameraInfo + iCanonMaxFocal);
    imgdata.other.CameraTemperature = 0.0f;
    break;
  case 0x80000174:
  case 0x80000188:
    iCanonCurFocal = 9;
    iCanonLensID = 12;
    iCanonMinFocal = 17;
    iCanonMaxFocal = 19;
    iCanonFocalType = 45;
    break;
  case 0x80000232:
    iCanonCurFocal = 9;
    iCanonLensID = 12;
    iCanonMinFocal = 17;
    iCanonMaxFocal = 19;
    break;
  case 0x80000169:
  case 0x80000215:
    iCanonCurFocal = 29;
    iCanonLensID = 273;
    iCanonMinFocal = 275;
    iCanonMaxFocal = 277;
    break;
  case 0x80000281:
    iCanonCurFocal = 30;
    iCanonLensID = 335;
    iCanonMinFocal = 337;
    iCanonMaxFocal = 339;
    break;
  case 0x80000269:
    iCanonCurFocal = 35;
    iCanonLensID = 423;
    iCanonMinFocal = 425;
    iCanonMaxFocal = 427;
    break;
  case 0x80000213:
    iCanonCurFocal = 40;
    if (!sget2Rev(CameraInfo + 12))
      iCanonLensID = 151;
    else
      iCanonLensID = 12;
    iCanonMinFocal = 147;
    iCanonMaxFocal = 149;
    break;
  case 0x80000218:
    iCanonCurFocal = 30;
    iCanonLensID = 230;
    iCanonMinFocal = 232;
    iCanonMaxFocal = 234;
    break;
  case 0x80000285:
    iCanonCurFocal = 35;
    iCanonLensID = 339;
    iCanonMinFocal = 341;
    iCanonMaxFocal = 343;
    break;
  case 0x80000302:
    iCanonCurFocal = 35;
    iCanonLensID = 353;
    iCanonMinFocal = 355;
    iCanonMaxFocal = 357;
    break;
  case 0x80000250:
    iCanonCurFocal = 30;
    iCanonLensID = 274;
    iCanonMinFocal = 276;
    iCanonMaxFocal = 278;
    break;
  case 0x80000190:
    iCanonCurFocal = 29;
    iCanonLensID = 214;
    iCanonMinFocal = 216;
    iCanonMaxFocal = 218;
    iCanonLens = 2347;
    break;
  case 0x80000261:
    iCanonCurFocal = 30;
    iCanonLensID = 234;
    iCanonMinFocal = 236;
    iCanonMaxFocal = 238;
    break;
  case 0x80000287:
    iCanonCurFocal = 30;
    iCanonLensID = 232;
    iCanonMinFocal = 234;
    iCanonMaxFocal = 236;
    break;
  case 0x80000325:
    iCanonCurFocal = 35;
    iCanonLensID = 358;
    iCanonMinFocal = 360;
    iCanonMaxFocal = 362;
    break;
  case 0x80000176:
    iCanonCurFocal = 29;
    iCanonLensID = 222;
    iCanonLens = 2355;
    break;
  case 0x80000252:
    iCanonCurFocal = 30;
    iCanonLensID = 246;
    iCanonMinFocal = 248;
    iCanonMaxFocal = 250;
    break;
  case 0x80000270:
    iCanonCurFocal = 30;
    iCanonLensID = 255;
    iCanonMinFocal = 257;
    iCanonMaxFocal = 259;
    break;
  case 0x80000286:
  case 0x80000288:
    iCanonCurFocal = 30;
    iCanonLensID = 234;
    iCanonMinFocal = 236;
    iCanonMaxFocal = 238;
    break;
  case 0x80000301:
  case 0x80000326:
    iCanonCurFocal = 35;
    iCanonLensID = 295;
    iCanonMinFocal = 297;
    iCanonMaxFocal = 299;
    break;
  case 0x80000254:
    iCanonCurFocal = 29;
    iCanonLensID = 226;
    iCanonMinFocal = 228;
    iCanonMaxFocal = 230;
    iCanonLens = 2359;
    break;
  }
  if (iCanonFocalType)
  {
    if (iCanonFocalType >= maxlen)
      return;
    imgdata.lens.makernotes.FocalType = CameraInfo[iCanonFocalType];
    if (!imgdata.lens.makernotes.FocalType)
      imgdata.lens.makernotes.FocalType = 1;
  }
  if (!imgdata.lens.makernotes.CurFocal)
  {
    if (iCanonCurFocal >= maxlen)
      return;
    imgdata.lens.makernotes.CurFocal = sget2Rev(CameraInfo + iCanonCurFocal);
  }
  if (!imgdata.lens.makernotes.LensID)
  {
    if (iCanonLensID >= maxlen)
      return;
    imgdata.lens.makernotes.LensID = sget2Rev(CameraInfo + iCanonLensID);
  }
  if (!imgdata.lens.makernotes.MinFocal)
  {
    if (iCanonMinFocal >= maxlen)
      return;
    imgdata.lens.makernotes.MinFocal = sget2Rev(CameraInfo + iCanonMinFocal);
  }
  if (!imgdata.lens.makernotes.MaxFocal)
  {
    if (iCanonMaxFocal >= maxlen)
      return;
    imgdata.lens.makernotes.MaxFocal = sget2Rev(CameraInfo + iCanonMaxFocal);
  }
  if (!imgdata.lens.makernotes.Lens[0] && iCanonLens)
  {
    if (iCanonLens + 64 >= maxlen)
      return;
    if (CameraInfo[iCanonLens] < 65)
    {
      memcpy(imgdata.lens.makernotes.Lens, CameraInfo + iCanonLens, 64);
    }
    else if (!strncmp((char *)CameraInfo + iCanonLens, "EF-S", 4))
    {
      memcpy(imgdata.lens.makernotes.Lens, "EF-S ", 5);
      memcpy(imgdata.lens.makernotes.LensFeatures_pre, "EF-E", 4);
      imgdata.lens.makernotes.LensMount = LIBRAW_MOUNT_Canon_EF_S;
      memcpy(imgdata.lens.makernotes.Lens + 5, CameraInfo + iCanonLens + 4, 60);
    }
    else if (!strncmp((char *)CameraInfo + iCanonLens, "TS-E", 4))
    {
      memcpy(imgdata.lens.makernotes.Lens, "TS-E ", 5);
      memcpy(imgdata.lens.makernotes.LensFeatures_pre, "TS-E", 4);
      imgdata.lens.makernotes.LensMount = LIBRAW_MOUNT_Canon_EF;
      memcpy(imgdata.lens.makernotes.Lens + 5, CameraInfo + iCanonLens + 4, 60);
    }
    else if (!strncmp((char *)CameraInfo + iCanonLens, "MP-E", 4))
    {
      memcpy(imgdata.lens.makernotes.Lens, "MP-E ", 5);
      memcpy(imgdata.lens.makernotes.LensFeatures_pre, "MP-E", 4);
      imgdata.lens.makernotes.LensMount = LIBRAW_MOUNT_Canon_EF;
      memcpy(imgdata.lens.makernotes.Lens + 5, CameraInfo + iCanonLens + 4, 60);
    }
    else if (!strncmp((char *)CameraInfo + iCanonLens, "EF-M", 4))
    {
      memcpy(imgdata.lens.makernotes.Lens, "EF-M ", 5);
      memcpy(imgdata.lens.makernotes.LensFeatures_pre, "EF-M", 4);
      imgdata.lens.makernotes.LensMount = LIBRAW_MOUNT_Canon_EF_M;
      memcpy(imgdata.lens.makernotes.Lens + 5, CameraInfo + iCanonLens + 4, 60);
    }
    else
    {
      memcpy(imgdata.lens.makernotes.Lens, CameraInfo + iCanonLens, 2);
      memcpy(imgdata.lens.makernotes.LensFeatures_pre, "EF", 2);
      imgdata.lens.makernotes.LensMount = LIBRAW_MOUNT_Canon_EF;
      imgdata.lens.makernotes.Lens[2] = 32;
      memcpy(imgdata.lens.makernotes.Lens + 3, CameraInfo + iCanonLens + 2, 62);
    }
  }
  return;
}
