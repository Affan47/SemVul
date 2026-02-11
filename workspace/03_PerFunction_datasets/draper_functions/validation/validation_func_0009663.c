imImageSetGray(imImage* image)
{
  assert(image);

  if (image->palette && image->data_type == IM_BYTE)
  {
    if (image->color_space == IM_BINARY)
    {
      image->palette_count = 256;
      for (int i = 0; i < 256; i++)
        image->palette[i] = imColorEncode((imbyte)i, (imbyte)i, (imbyte)i);
    }
    image->color_space = IM_GRAY;
  }
}
