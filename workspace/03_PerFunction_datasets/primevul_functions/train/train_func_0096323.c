void Magick::Image::pixelColor(const ssize_t x_,const ssize_t y_,
  const Color &color_)
{
  PixelInfo
    packet;

  Quantum
    *pixel;


  if (y_ > (ssize_t) rows() || x_ > (ssize_t) columns())
    throwExceptionExplicit(MagickCore::OptionError,
      "Access outside of image boundary");

  modifyImage();


  classType(DirectClass );


  Pixels pixels(*this);

  pixel=pixels.get(x_, y_, 1, 1 );
  packet=color_;
  MagickCore::SetPixelViaPixelInfo(constImage(),&packet,pixel);

  pixels.sync();
}
