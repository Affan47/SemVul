FormatNew2Old(const char* new_format, const char* compression)
{
  int format;

  if (!imStrEqual(new_format, "BMP"))
    format = IM_BMP;
  else if (!imStrEqual(new_format, "GIF"))
    format = IM_GIF;
  else if (!imStrEqual(new_format, "PCX"))
    format = IM_PCX;
  else if (!imStrEqual(new_format, "RAS"))
    format = IM_RAS;
  else if (!imStrEqual(new_format, "SGI"))
    format = IM_SGI;
  else if (!imStrEqual(new_format, "JPEG"))
    format = IM_JPG;
  else if (!imStrEqual(new_format, "LED"))
    format = IM_LED;
  else if (!imStrEqual(new_format, "TIFF"))
    format = IM_TIF;
  else if (!imStrEqual(new_format, "TGA"))
    format = IM_TGA;
  else
    return -1;

  if (!imStrEqual(compression, "NONE"))
    format |= IM_DEFAULT;

  return format;
}
