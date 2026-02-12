void LibRaw::process_Sony_0x0116(uchar *buf, ushort len, unsigned long long id)
{
  int i = 0;

  if (((id == 0x101ULL) ||
       (id == 0x106ULL) ||
       (id == 0x10dULL) ||
       (id == 0x10eULL)
       ) &&
      (len >= 2))
    i = 1;
  else if ((id >= 0x111ULL) && (len >= 3))
    i = 2;
  else
    return;

  imgdata.makernotes.common.BatteryTemperature = (float)(buf[i] - 32) / 1.8f;
}
