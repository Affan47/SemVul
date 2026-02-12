MagickExport MagickBooleanType ResamplePixelColor(
  ResampleFilter *resample_filter,const double u0,const double v0,
  PixelInfo *pixel,ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  ssize_t u,v, v1, v2, uw, hit;
  double u1;
  double U,V,Q,DQ,DDQ;
  double divisor_c,divisor_m;
  double weight;
  const Quantum *pixels;
  assert(resample_filter != (ResampleFilter *) NULL);
  assert(resample_filter->signature == MagickCoreSignature);

  status=MagickTrue;

  if ( resample_filter->do_interpolate ) {
    status=InterpolatePixelInfo(resample_filter->image,resample_filter->view,
      resample_filter->interpolate,u0,v0,pixel,resample_filter->exception);
    return(status);
  }

#if DEBUG_ELLIPSE
  (void) FormatLocaleFile(stderr, "u0=%lf; v0=%lf;\n", u0, v0);
#endif


  hit = 0;
  switch ( resample_filter->virtual_pixel ) {
    case BackgroundVirtualPixelMethod:
    case TransparentVirtualPixelMethod:
    case BlackVirtualPixelMethod:
    case GrayVirtualPixelMethod:
    case WhiteVirtualPixelMethod:
    case MaskVirtualPixelMethod:
      if ( resample_filter->limit_reached
           || u0 + resample_filter->Ulimit < 0.0
           || u0 - resample_filter->Ulimit > (double) resample_filter->image->columns-1.0
           || v0 + resample_filter->Vlimit < 0.0
           || v0 - resample_filter->Vlimit > (double) resample_filter->image->rows-1.0
           )
        hit++;
      break;

    case UndefinedVirtualPixelMethod:
    case EdgeVirtualPixelMethod:
      if (    ( u0 + resample_filter->Ulimit < 0.0 && v0 + resample_filter->Vlimit < 0.0 )
           || ( u0 + resample_filter->Ulimit < 0.0
                && v0 - resample_filter->Vlimit > (double) resample_filter->image->rows-1.0 )
           || ( u0 - resample_filter->Ulimit > (double) resample_filter->image->columns-1.0
                && v0 + resample_filter->Vlimit < 0.0 )
           || ( u0 - resample_filter->Ulimit > (double) resample_filter->image->columns-1.0
                && v0 - resample_filter->Vlimit > (double) resample_filter->image->rows-1.0 )
           )
        hit++;
      break;
    case HorizontalTileVirtualPixelMethod:
      if (    v0 + resample_filter->Vlimit < 0.0
           || v0 - resample_filter->Vlimit > (double) resample_filter->image->rows-1.0
           )
        hit++;
      break;
    case VerticalTileVirtualPixelMethod:
      if (    u0 + resample_filter->Ulimit < 0.0
           || u0 - resample_filter->Ulimit > (double) resample_filter->image->columns-1.0
           )
        hit++;
      break;
    case DitherVirtualPixelMethod:
      if (    ( u0 + resample_filter->Ulimit < -32.0 && v0 + resample_filter->Vlimit < -32.0 )
           || ( u0 + resample_filter->Ulimit < -32.0
                && v0 - resample_filter->Vlimit > (double) resample_filter->image->rows+31.0 )
           || ( u0 - resample_filter->Ulimit > (double) resample_filter->image->columns+31.0
                && v0 + resample_filter->Vlimit < -32.0 )
           || ( u0 - resample_filter->Ulimit > (double) resample_filter->image->columns+31.0
                && v0 - resample_filter->Vlimit > (double) resample_filter->image->rows+31.0 )
           )
        hit++;
      break;
    case TileVirtualPixelMethod:
    case MirrorVirtualPixelMethod:
    case RandomVirtualPixelMethod:
    case HorizontalTileEdgeVirtualPixelMethod:
    case VerticalTileEdgeVirtualPixelMethod:
    case CheckerTileVirtualPixelMethod:

      break;
  }
  if ( hit ) {


    status=InterpolatePixelInfo(resample_filter->image,resample_filter->view,
      IntegerInterpolatePixel,u0,v0,pixel,resample_filter->exception);
    return(status);
  }


  if ( resample_filter->limit_reached ) {
    switch ( resample_filter->virtual_pixel ) {


      case UndefinedVirtualPixelMethod:
      case EdgeVirtualPixelMethod:
      case DitherVirtualPixelMethod:
      case HorizontalTileEdgeVirtualPixelMethod:
      case VerticalTileEdgeVirtualPixelMethod:


        status=InterpolatePixelInfo(resample_filter->image,
          resample_filter->view,AverageInterpolatePixel,u0,v0,pixel,
          resample_filter->exception);
        break;
      case HorizontalTileVirtualPixelMethod:
      case VerticalTileVirtualPixelMethod:

        status=InterpolatePixelInfo(resample_filter->image,
          resample_filter->view,IntegerInterpolatePixel,-1.0,-1.0,pixel,
          resample_filter->exception);
        break;
      case TileVirtualPixelMethod:
      case MirrorVirtualPixelMethod:
      case RandomVirtualPixelMethod:
      case CheckerTileVirtualPixelMethod:
      default:

        if ( resample_filter->average_defined == MagickFalse ) {
          Image
            *average_image;

          CacheView
            *average_view;

          GetPixelInfo(resample_filter->image,(PixelInfo *)
            &resample_filter->average_pixel);
          resample_filter->average_defined=MagickTrue;


          average_image=ResizeImage(resample_filter->image,1,1,BoxFilter,
            resample_filter->exception);
          if (average_image == (Image *) NULL)
            {
              *pixel=resample_filter->average_pixel;
              break;
            }
          average_view=AcquireVirtualCacheView(average_image,exception);
          pixels=GetCacheViewVirtualPixels(average_view,0,0,1,1,
            resample_filter->exception);
          if (pixels == (const Quantum *) NULL) {
            average_view=DestroyCacheView(average_view);
            average_image=DestroyImage(average_image);
            *pixel=resample_filter->average_pixel;
            break;
          }
          GetPixelInfoPixel(resample_filter->image,pixels,
            &(resample_filter->average_pixel));
          average_view=DestroyCacheView(average_view);
          average_image=DestroyImage(average_image);

          if ( resample_filter->virtual_pixel == CheckerTileVirtualPixelMethod )
            {


              weight = QuantumScale*((double)
                resample_filter->average_pixel.alpha);
              resample_filter->average_pixel.red *= weight;
              resample_filter->average_pixel.green *= weight;
              resample_filter->average_pixel.blue *= weight;
              divisor_c = weight;


              weight = QuantumScale*((double)
                resample_filter->image->background_color.alpha);
              resample_filter->average_pixel.red +=
                      weight*resample_filter->image->background_color.red;
              resample_filter->average_pixel.green +=
                      weight*resample_filter->image->background_color.green;
              resample_filter->average_pixel.blue +=
                      weight*resample_filter->image->background_color.blue;
              resample_filter->average_pixel.alpha +=
                      resample_filter->image->background_color.alpha;
              divisor_c += weight;


              resample_filter->average_pixel.red /= divisor_c;
              resample_filter->average_pixel.green /= divisor_c;
              resample_filter->average_pixel.blue /= divisor_c;
              resample_filter->average_pixel.alpha /= 2;

            }
        }
        *pixel=resample_filter->average_pixel;
        break;
    }
    return(status);
  }


  hit = 0;
  divisor_c = 0.0;
  divisor_m = 0.0;
  pixel->red = pixel->green = pixel->blue = 0.0;
  if (pixel->colorspace == CMYKColorspace)
    pixel->black = 0.0;
  if (pixel->alpha_trait != UndefinedPixelTrait)
    pixel->alpha = 0.0;


  v1 = (ssize_t)ceil(v0 - resample_filter->Vlimit);
  v2 = (ssize_t)floor(v0 + resample_filter->Vlimit);


  u1 = u0 + (v1-v0)*resample_filter->slope - resample_filter->Uwidth;
  uw = (ssize_t)(2.0*resample_filter->Uwidth)+1;

#if DEBUG_ELLIPSE
  (void) FormatLocaleFile(stderr, "v1=%ld; v2=%ld\n", (long)v1, (long)v2);
  (void) FormatLocaleFile(stderr, "u1=%ld; uw=%ld\n", (long)u1, (long)uw);
#else
# define DEBUG_HIT_MISS 0
#endif


  DDQ = 2*resample_filter->A;
  for( v=v1; v<=v2;  v++ ) {
#if DEBUG_HIT_MISS
    long uu = ceil(u1);
    (void) FormatLocaleFile(stderr, "# scan line from pixel %ld, %ld\n", (long)uu, (long)v);
#endif
    u = (ssize_t)ceil(u1);
    u1 += resample_filter->slope;


    U = (double)u-u0;
    V = (double)v-v0;


    Q = (resample_filter->A*U + resample_filter->B*V)*U + resample_filter->C*V*V;
    DQ = resample_filter->A*(2.0*U+1) + resample_filter->B*V;


    pixels=GetCacheViewVirtualPixels(resample_filter->view,u,v,(size_t) uw,
      1,resample_filter->exception);
    if (pixels == (const Quantum *) NULL)
      return(MagickFalse);


    for( u=0; u<uw; u++ ) {
#if FILTER_LUT

      if ( Q < (double)WLUT_WIDTH ) {
        weight = resample_filter->filter_lut[(int)Q];
#else

      if ( Q < (double)resample_filter->F ) {
        weight = GetResizeFilterWeight(resample_filter->filter_def,
             sqrt(Q));
#endif

        pixel->alpha  += weight*GetPixelAlpha(resample_filter->image,pixels);
        divisor_m += weight;

        if (pixel->alpha_trait != UndefinedPixelTrait)
          weight *= QuantumScale*((double) GetPixelAlpha(resample_filter->image,pixels));
        pixel->red   += weight*GetPixelRed(resample_filter->image,pixels);
        pixel->green += weight*GetPixelGreen(resample_filter->image,pixels);
        pixel->blue  += weight*GetPixelBlue(resample_filter->image,pixels);
        if (pixel->colorspace == CMYKColorspace)
          pixel->black += weight*GetPixelBlack(resample_filter->image,pixels);
        divisor_c += weight;

        hit++;
#if DEBUG_HIT_MISS

        (void) FormatLocaleFile(stderr, "set arrow from %lf,%lf to %lf,%lf nohead ls 3\n",
                     (long)uu-.1,(double)v-.1,(long)uu+.1,(long)v+.1);
        (void) FormatLocaleFile(stderr, "set arrow from %lf,%lf to %lf,%lf nohead ls 3\n",
                     (long)uu+.1,(double)v-.1,(long)uu-.1,(long)v+.1);
      } else {
        (void) FormatLocaleFile(stderr, "set arrow from %lf,%lf to %lf,%lf nohead ls 1\n",
                     (long)uu-.1,(double)v-.1,(long)uu+.1,(long)v+.1);
        (void) FormatLocaleFile(stderr, "set arrow from %lf,%lf to %lf,%lf nohead ls 1\n",
                     (long)uu+.1,(double)v-.1,(long)uu-.1,(long)v+.1);
      }
      uu++;
#else
      }
#endif
      pixels+=GetPixelChannels(resample_filter->image);
      Q += DQ;
      DQ += DDQ;
    }
  }
#if DEBUG_ELLIPSE
  (void) FormatLocaleFile(stderr, "Hit=%ld;  Total=%ld;\n", (long)hit, (long)uw*(v2-v1) );
#endif


  if ( hit == 0 || divisor_m <= MagickEpsilon || divisor_c <= MagickEpsilon ) {


#if DEBUG_NO_PIXEL_HIT
    pixel->alpha = pixel->red = pixel->green = pixel->blue = 0;
    pixel->red = QuantumRange;
#else
    status=InterpolatePixelInfo(resample_filter->image,
      resample_filter->view,resample_filter->interpolate,u0,v0,pixel,
      resample_filter->exception);
#endif
    return status;
  }


  divisor_m = 1.0/divisor_m;
  if (pixel->alpha_trait != UndefinedPixelTrait)
    pixel->alpha = (double) ClampToQuantum(divisor_m*pixel->alpha);
  divisor_c = 1.0/divisor_c;
  pixel->red   = (double) ClampToQuantum(divisor_c*pixel->red);
  pixel->green = (double) ClampToQuantum(divisor_c*pixel->green);
  pixel->blue  = (double) ClampToQuantum(divisor_c*pixel->blue);
  if (pixel->colorspace == CMYKColorspace)
    pixel->black = (double) ClampToQuantum(divisor_c*pixel->black);
  return(MagickTrue);
}
