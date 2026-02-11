Bitmap_mask(dword pixel, dword mask)
{
  byte result;
  int i;
  int bits_found;

  switch(mask)
  {

    case 0x000000FF:
      return (pixel & 0x000000FF);
    case 0x0000FF00:
      return (pixel & 0x0000FF00)>>8;
    case 0x00FF0000:
      return (pixel & 0x00FF0000)>>16;
    case 0xFF000000:
      return (pixel & 0xFF000000)>>24;
  }

  bits_found=0;
  result=0;

  for (i=0;i<32;i++)
  {

    if (mask & (1<<i))
    {
      if (pixel & 1<<i)
        result |= 1<<bits_found;

      bits_found++;

      if (bits_found>=8)
        return result;
    }
  }

  return result << (8-bits_found);
}
