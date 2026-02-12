MagickPPExport int Magick::operator == (const Magick::Image &left_,
  const Magick::Image &right_)
{

  return((left_.rows() == right_.rows()) &&
    (left_.columns() == right_.columns()) &&
    (left_.signature() == right_.signature()));
}
