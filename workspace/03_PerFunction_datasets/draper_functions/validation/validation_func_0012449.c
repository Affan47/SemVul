New(const char* file_name)
{

  handle = imBinFileNew(file_name);
  if (!handle)
    return IM_ERR_OPEN;

  this->image_count = 1;

  return IM_ERR_NONE;
}
