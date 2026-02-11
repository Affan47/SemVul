imProcessDifusionErrThreshold(const imImage* src_image, imImage* dst_image, int level)
{
  int value = src_image->depth > 1? 255: 1;
  for (int i = 0; i < src_image->depth; i++)
  {
    do_dither_error((imbyte*)src_image->data[i], (imbyte*)dst_image->data[i], src_image->count, level, value);
  }
}
