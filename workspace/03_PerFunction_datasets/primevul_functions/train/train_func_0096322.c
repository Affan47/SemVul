MagickPPExport int Magick::operator < (const Magick::Image &left_,
  const Magick::Image &right_)
{

  return((left_.rows() * left_.columns()) <
    (right_.rows() * right_.columns()));
}
