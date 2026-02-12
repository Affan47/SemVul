void LibRaw::Canon_CameraSettings(unsigned len)
{
  fseek(ifp, 10, SEEK_CUR);
  imgdata.shootinginfo.DriveMode = get2();
  get2();
  imgdata.shootinginfo.FocusMode = get2();
  fseek(ifp, 18, SEEK_CUR);
  imgdata.shootinginfo.MeteringMode = get2();
  get2();
  imgdata.shootinginfo.AFPoint = get2();
  imgdata.shootinginfo.ExposureMode = get2();
  get2();
  ilm.LensID = get2();
  ilm.MaxFocal = get2();
  ilm.MinFocal = get2();
  ilm.FocalUnits = get2();
  if (ilm.FocalUnits > 1)
  {
    ilm.MaxFocal /= (float)ilm.FocalUnits;
    ilm.MinFocal /= (float)ilm.FocalUnits;
  }
  ilm.MaxAp = _CanonConvertAperture(get2());
  ilm.MinAp = _CanonConvertAperture(get2());
  if (len >= 36)
  {
    fseek(ifp, 12, SEEK_CUR);
    imgdata.shootinginfo.ImageStabilization = get2();
  }
  else
    return;
  if (len >= 48)
  {
    fseek(ifp, 22, SEEK_CUR);
    imCanon.SRAWQuality = get2();
  }
}
