void LibRaw::parseLeicaMakernote(int base, int uptag, unsigned MakernoteTagType)
{
  int c;
  uchar ci, cj;
  unsigned offset = 0, entries, tag, type, len, save;
  short morder, sorder = order;
  char buf[10];
  int LeicaMakernoteSignature = -1;
  INT64 fsize = ifp->size();
  fread(buf, 1, 10, ifp);
  if (strncmp(buf, "LEICA", 5))
  {
    fseek(ifp, -10, SEEK_CUR);
    if (uptag == 0x3400)
      LeicaMakernoteSignature = 0x3400;
    else
      LeicaMakernoteSignature = -2;
  }
  else
  {
    fseek(ifp, -2, SEEK_CUR);
    LeicaMakernoteSignature = ((uchar)buf[6] << 8) | (uchar)buf[7];
    if (!LeicaMakernoteSignature &&
        (!strncmp(model, "M8", 2) || !strncmp(model + 6, "M8", 2)))
      LeicaMakernoteSignature = -3;
    if ((LeicaMakernoteSignature != 0x0000) &&
        (LeicaMakernoteSignature != 0x0800) &&
        (LeicaMakernoteSignature != 0x0900) &&
        (LeicaMakernoteSignature != 0x02ff))
      base = ftell(ifp) - 8;
  }
  setLeicaBodyFeatures(LeicaMakernoteSignature);

  entries = get2();
  if (entries > 1000)
    return;
  morder = order;

  while (entries--)
  {
    order = morder;
    tiff_get(base, &tag, &type, &len, &save);

    INT64 pos = ifp->tell();
    if (len > 8 && pos + len > 2 * fsize)
    {
      fseek(ifp, save, SEEK_SET);
      continue;
    }
    tag |= uptag << 16;
    if (len > 100 * 1024 * 1024)
      goto next;

    if (LeicaMakernoteSignature == -3)
    {
      if (tag == 0x0310)
      {
        parseLeicaLensID();
      }
      else if ((tag == 0x0313) && (fabs(ilm.CurAp) < 0.17f))
      {
        ilm.CurAp = getreal(type);
        if (ilm.CurAp > 126.3)
        {
          ilm.CurAp = 0.0f;
        }
      }
      else if (tag == 0x0320)
      {
        imgdata.makernotes.common.CameraTemperature = getreal(type);
      }
    }
    else if (LeicaMakernoteSignature == -2)
    {
      if (tag == 0x000d)
      {
        FORC3 cam_mul[c] = get2();
        cam_mul[3] = cam_mul[1];
      }
    }
    else if (LeicaMakernoteSignature == 0)
    {
      if (tag == 0x0007)
      {
        imgdata.shootinginfo.FocusMode = get2();
      }
      else if (tag == 0x001a)
      {
        imgdata.shootinginfo.ImageStabilization = get2();
      }
    }
    else if ((LeicaMakernoteSignature == 0x0100) ||
             (LeicaMakernoteSignature == 0x0400) ||
             (LeicaMakernoteSignature == 0x0500) ||
             (LeicaMakernoteSignature == 0x0700) ||
             (LeicaMakernoteSignature == 0x1000))
    {
      if (tag == 0x040d)
      {
        ci = fgetc(ifp);
        cj = fgetc(ifp);
        imgdata.shootinginfo.ExposureMode = ((ushort)ci << 8) | cj;
      }
    }
    else if ((LeicaMakernoteSignature == 0x0600) ||
             (LeicaMakernoteSignature == 0x1a00))
    {
      if (tag == 0x040d)
      {
        ci = fgetc(ifp);
        cj = fgetc(ifp);
        imgdata.shootinginfo.ExposureMode = ((ushort)ci << 8) | cj;
      }
      else if (tag == 0x0303)
      {
        parseLeicaLensName(len);
      }
    }
    else if (LeicaMakernoteSignature == 0x0200)
    {
    }
    else if (LeicaMakernoteSignature == 0x02ff)
    {

      if (tag == 0x0303)
      {
        if (parseLeicaLensName(len))
        {
          ilm.LensMount = ilm.CameraMount;
          ilm.LensFormat = ilm.CameraFormat;
        }
      }
    }
    else if (LeicaMakernoteSignature == 0x0300)
    {
      if (tag == 0x3400)
      {
        parseLeicaMakernote(base, 0x3400, MakernoteTagType);
      }
    }
    else if ((LeicaMakernoteSignature == 0x0800) ||
             (LeicaMakernoteSignature == 0x0900))
    {
      if ((tag == 0x0304) && (len == 1) && ((c = fgetc(ifp)) != 0) &&
          (ilm.CameraMount == LIBRAW_MOUNT_Leica_L))
      {
        strcpy(ilm.Adapter, "M-Adapter L");
        ilm.LensMount = LIBRAW_MOUNT_Leica_M;
        ilm.LensFormat = LIBRAW_FORMAT_FF;
        ilm.LensID = c * 256;
      }
      else if (tag == 0x0500)
      {
        parseLeicaInternalBodySerial(len);
      }
    }
    else if (LeicaMakernoteSignature == 0x3400)
    {
      if (tag == 0x34003402)
      {
        imgdata.makernotes.common.CameraTemperature = getreal(type);
      }
      else if (tag == 0x34003405)
      {
        parseLeicaLensID();
      }
      else if ((tag == 0x34003406) && (fabs(ilm.CurAp) < 0.17f))
      {
        ilm.CurAp = getreal(type);
        if (ilm.CurAp > 126.3)
        {
          ilm.CurAp = 0.0f;
        }
      }
    }

  next:
    fseek(ifp, save, SEEK_SET);
  }
quit:
  order = sorder;
}
