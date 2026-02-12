Magick::Image& Magick::Image::operator=(const Magick::Image &image_)
{
  if (this != &image_)
    {
      image_._imgRef->increase();
      if (_imgRef->decrease() == 0)
        delete _imgRef;


      _imgRef=image_._imgRef;
    }
  return(*this);
}
