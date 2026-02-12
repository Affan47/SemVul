void Magick::Image::classType(const ClassType class_)
{
  if (classType() == PseudoClass && class_ == DirectClass)
    {


      modifyImage();
      GetPPException;
      SyncImage(image(),exceptionInfo);
      ThrowImageException;
      image()->colormap=(PixelInfo *)RelinquishMagickMemory(image()->colormap);
      image()->storage_class=static_cast<MagickCore::ClassType>(DirectClass);
      return;
    }

  if (classType() == DirectClass && class_ == PseudoClass)
    {

      modifyImage();
      quantizeColors(MaxColormapSize);
      quantize();
      image()->storage_class=static_cast<MagickCore::ClassType>(PseudoClass);
    }
}
