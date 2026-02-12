Magick::Image::Image(const Geometry &size_,const Color &color_)
  : _imgRef(new ImageRef)
{

  std::string imageSpec("xc:");
  imageSpec+=color_;

  try
  {
    quiet(true);

    size(size_);


    read(imageSpec);
    quiet(false);
  }
  catch(const Error&)
  {

    delete _imgRef;
    throw;
  }
}
