GetSimilarityMetric(const Image *image,const Image *reference,
  const ssize_t x_offset,const ssize_t y_offset,
  const double similarity_threshold,ExceptionInfo *exception)
{
  CacheView
    *image_view,
    *reference_view;

  double
    channels,
    normalized_similarity,
    similarity;

  ssize_t
    y;


  normalized_similarity=1.0;
  similarity=0.0;
  channels=3;
  if ((image->matte != MagickFalse) && (reference->matte != MagickFalse))
    channels++;
  if ((image->colorspace == CMYKColorspace) &&
      (reference->colorspace == CMYKColorspace))
    channels++;
  image_view=AcquireVirtualCacheView(image,exception);
  reference_view=AcquireVirtualCacheView(reference,exception);
  for (y=0; y < (ssize_t) reference->rows; y++)
  {
    register const IndexPacket
      *indexes,
      *reference_indexes;

    register const PixelPacket
      *p,
      *q;

    register ssize_t
      x;

    p=GetCacheViewVirtualPixels(image_view,x_offset,y_offset+y,
      reference->columns,1,exception);
    q=GetCacheViewVirtualPixels(reference_view,0,y,reference->columns,1,
      exception);
    if ((p == (const PixelPacket *) NULL) || (q == (const PixelPacket *) NULL))
      continue;
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    reference_indexes=GetCacheViewVirtualIndexQueue(reference_view);
    for (x=0; x < (ssize_t) reference->columns; x++)
    {
      MagickRealType
        pixel;

      pixel=QuantumScale*(GetPixelRed(p)-(double)
        GetPixelRed(q));
      similarity+=pixel*pixel;
      pixel=QuantumScale*(GetPixelGreen(p)-(double)
        GetPixelGreen(q));
      similarity+=pixel*pixel;
      pixel=QuantumScale*(GetPixelBlue(p)-(double)
        GetPixelBlue(q));
      similarity+=pixel*pixel;
      if ((image->matte != MagickFalse) && (reference->matte != MagickFalse))
        {
          pixel=QuantumScale*(GetPixelOpacity(p)-(double)
            GetPixelOpacity(q));
          similarity+=pixel*pixel;
        }
      if ((image->colorspace == CMYKColorspace) &&
          (reference->colorspace == CMYKColorspace))
        {
          pixel=QuantumScale*(GetPixelIndex(indexes+x)-(double)
            GetPixelIndex(reference_indexes+x));
          similarity+=pixel*pixel;
        }
      p++;
      q++;
    }
    normalized_similarity=sqrt(similarity)/reference->columns/reference->rows/
      channels;
    if (normalized_similarity > similarity_threshold)
      break;
  }
  reference_view=DestroyCacheView(reference_view);
  image_view=DestroyCacheView(image_view);
  return(normalized_similarity);
}
