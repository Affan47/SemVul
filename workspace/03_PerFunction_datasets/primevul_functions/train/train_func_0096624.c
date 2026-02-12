Magick::Image::Image(const Blob &blob_)
  : _imgRef(new ImageRef)
{
  try
  {

    quiet(true);
    read(blob_);
    quiet(false);
  }
  catch (const Error&)
  {

    delete _imgRef;
    throw;
  }
}
