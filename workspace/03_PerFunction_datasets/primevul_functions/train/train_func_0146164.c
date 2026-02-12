MagickExport MagickBooleanType IsFuzzyEquivalencePixel(const Image *source,
  const Quantum *p,const Image *destination,const Quantum *q)
{
  double
    fuzz,
    pixel;

  register double
    distance,
    scale;

  fuzz=GetFuzzyColorDistance(source,destination);
  scale=1.0;
  distance=0.0;
  if (source->alpha_trait != UndefinedPixelTrait ||
      destination->alpha_trait != UndefinedPixelTrait)
    {


      pixel=GetPixelAlpha(source,p)-(double) GetPixelAlpha(destination,q);
      distance=pixel*pixel;
      if (distance > fuzz)
        return(MagickFalse);


      if (source->alpha_trait != UndefinedPixelTrait)
        scale=QuantumScale*GetPixelAlpha(source,p);
      if (destination->alpha_trait != UndefinedPixelTrait)
        scale*=QuantumScale*GetPixelAlpha(destination,q);
      if (scale <= MagickEpsilon)
        return(MagickTrue);
    }


  distance*=3.0;
  fuzz*=3.0;
  pixel=GetPixelRed(source,p)-(double) GetPixelRed(destination,q);
  if ((source->colorspace == HSLColorspace) ||
      (source->colorspace == HSBColorspace) ||
      (source->colorspace == HWBColorspace))
    {


      if (fabs((double) pixel) > (QuantumRange/2))
        pixel-=QuantumRange;
      pixel*=2;
    }
  distance+=scale*pixel*pixel;
  if (distance > fuzz)
    return(MagickFalse);
  pixel=GetPixelGreen(source,p)-(double) GetPixelGreen(destination,q);
  distance+=scale*pixel*pixel;
  if (distance > fuzz)
    return(MagickFalse);
  pixel=GetPixelBlue(source,p)-(double) GetPixelBlue(destination,q);
  distance+=scale*pixel*pixel;
  if (distance > fuzz)
    return(MagickFalse);
  return(MagickTrue);
}
