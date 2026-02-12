void Magick::Image::read(const Blob &blob_,const Geometry &size_,
  const std::string &magick_)
{
  size(size_);
  magick(magick_);

  fileName(magick_ + ':');
  read(blob_);
}
