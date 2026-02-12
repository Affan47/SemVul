Magick::Image::Image(const Blob &blob_,const Geometry &size_,
  const size_t depth_)
  : _imgRef(new ImageRef)
{
  try
  {

    quiet(true);
    read(blob_,size_,depth_);
    quiet(false);
  }
  catch(const Error&)
  {

    delete _imgRef;
    throw;
  }
}
