void Magick::Image::alpha(const bool alphaFlag_)
{
  modifyImage();


  GetPPException;
  if ((alphaFlag_ && !constImage()->alpha_trait) ||
      (constImage()->alpha_trait && !alphaFlag_))
    SetImageAlpha(image(),OpaqueAlpha,exceptionInfo);
  ThrowImageException;

  image()->alpha_trait=alphaFlag_ ? BlendPixelTrait : UndefinedPixelTrait;
}
