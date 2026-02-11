imImageCheckFormat(int color_mode, int data_type)
{
  if ((imColorModeSpace(color_mode) == IM_MAP || imColorModeSpace(color_mode) == IM_BINARY) &&
      (data_type != IM_BYTE))
    return 0;

  return 1;
}
