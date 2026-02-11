IsValid(PhotometricInterpretation const &pi)
{
  bool ret = false;
  switch( pi )
    {

    case PhotometricInterpretation::MONOCHROME1:
    case PhotometricInterpretation::MONOCHROME2:
    case PhotometricInterpretation::PALETTE_COLOR:
    case PhotometricInterpretation::RGB:
    case PhotometricInterpretation::YBR_FULL:
    case PhotometricInterpretation::YBR_FULL_422:
    case PhotometricInterpretation::YBR_PARTIAL_422:
    case PhotometricInterpretation::YBR_PARTIAL_420:
      ret = true;
      break;
    default:
      ;


    }
  return ret;
}
