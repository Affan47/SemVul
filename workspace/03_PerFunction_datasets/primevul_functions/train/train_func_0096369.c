void Magick::Image::isValid(const bool isValid_)
{
  if (!isValid_)
    {
      delete _imgRef;
      _imgRef=new ImageRef;
    }
  else if (!isValid())
    {


      size(Geometry(1,1));
      read("xc:black");
    }
}
