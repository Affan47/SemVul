Magick::Image::Image(const std::string &imageSpec_)
  : _imgRef(new ImageRef)
{
  try
  {

    quiet(true);
    read(imageSpec_);
    quiet(false);
  }
  catch(const Error&)
  {

    delete _imgRef;
    throw;
  }
}
