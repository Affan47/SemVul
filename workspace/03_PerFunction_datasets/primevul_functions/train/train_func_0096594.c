Magick::Image Magick::Image::fillPattern(void) const
{

  const MagickCore::Image
    *tmpTexture;

  Image
    texture;

  tmpTexture=constOptions()->fillPattern();

  if (tmpTexture)
    {
      MagickCore::Image
        *image;

      GetPPException;
      image=CloneImage(tmpTexture,0,0,MagickTrue,exceptionInfo);
      texture.replaceImage(image);
      ThrowImageException;
    }
  return(texture);
}
