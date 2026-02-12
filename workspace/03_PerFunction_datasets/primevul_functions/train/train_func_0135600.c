MagickPrivate ResizeFilter *AcquireResizeFilter(const Image *image,
  const FilterType filter,const MagickBooleanType cylindrical,
  ExceptionInfo *exception)
{
  const char
    *artifact;

  FilterType
    filter_type,
    window_type;

  double
    B,
    C,
    value;

  register ResizeFilter
    *resize_filter;


  static struct
  {
    FilterType
      filter,
      window;
  } const mapping[SentinelFilter] =
  {
    { UndefinedFilter,     BoxFilter      },
    { PointFilter,         BoxFilter      },
    { BoxFilter,           BoxFilter      },
    { TriangleFilter,      BoxFilter      },
    { HermiteFilter,       BoxFilter      },
    { SincFastFilter,      HannFilter     },
    { SincFastFilter,      HammingFilter  },
    { SincFastFilter,      BlackmanFilter },
    { GaussianFilter,      BoxFilter      },
    { QuadraticFilter,     BoxFilter      },
    { CubicFilter,         BoxFilter      },
    { CatromFilter,        BoxFilter      },
    { MitchellFilter,      BoxFilter      },
    { JincFilter,          BoxFilter      },
    { SincFilter,          BoxFilter      },
    { SincFastFilter,      BoxFilter      },
    { SincFastFilter,      KaiserFilter   },
    { LanczosFilter,       WelchFilter    },
    { SincFastFilter,      CubicFilter    },
    { SincFastFilter,      BohmanFilter   },
    { SincFastFilter,      TriangleFilter },
    { LagrangeFilter,      BoxFilter      },
    { LanczosFilter,       LanczosFilter  },
    { LanczosSharpFilter,  LanczosSharpFilter },
    { Lanczos2Filter,      Lanczos2Filter },
    { Lanczos2SharpFilter, Lanczos2SharpFilter },
    { RobidouxFilter,      BoxFilter      },
    { RobidouxSharpFilter, BoxFilter      },
    { LanczosFilter,       CosineFilter   },
    { SplineFilter,        BoxFilter      },
    { LanczosRadiusFilter, LanczosFilter  },
    { CubicSplineFilter,   BoxFilter      },
  };


  static struct
  {
    double
      (*function)(const double,const ResizeFilter*),
      support,
      scale,

      B,C;
    ResizeWeightingFunctionType weightingFunctionType;
  } const filters[SentinelFilter] =
  {


    { Box,       0.5, 0.5, 0.0, 0.0, BoxWeightingFunction },
    { Box,       0.0, 0.5, 0.0, 0.0, BoxWeightingFunction },
    { Box,       0.5, 0.5, 0.0, 0.0, BoxWeightingFunction },
    { Triangle,  1.0, 1.0, 0.0, 0.0, TriangleWeightingFunction },
    { CubicBC,   1.0, 1.0, 0.0, 0.0, CubicBCWeightingFunction },
    { Hann,      1.0, 1.0, 0.0, 0.0, HannWeightingFunction },
    { Hamming,   1.0, 1.0, 0.0, 0.0, HammingWeightingFunction },
    { Blackman,  1.0, 1.0, 0.0, 0.0, BlackmanWeightingFunction },
    { Gaussian,  2.0, 1.5, 0.0, 0.0, GaussianWeightingFunction },
    { Quadratic, 1.5, 1.5, 0.0, 0.0, QuadraticWeightingFunction },
    { CubicBC,   2.0, 2.0, 1.0, 0.0, CubicBCWeightingFunction },
    { CubicBC,   2.0, 1.0, 0.0, 0.5, CubicBCWeightingFunction },
    { CubicBC,   2.0, 8.0/7.0, 1./3., 1./3., CubicBCWeightingFunction },
    { Jinc,      3.0, 1.2196698912665045, 0.0, 0.0, JincWeightingFunction },
    { Sinc,      4.0, 1.0, 0.0, 0.0, SincWeightingFunction },
    { SincFast,  4.0, 1.0, 0.0, 0.0, SincFastWeightingFunction },
    { Kaiser,    1.0, 1.0, 0.0, 0.0, KaiserWeightingFunction },
    { Welch,     1.0, 1.0, 0.0, 0.0, WelchWeightingFunction },
    { CubicBC,   2.0, 2.0, 1.0, 0.0, CubicBCWeightingFunction },
    { Bohman,    1.0, 1.0, 0.0, 0.0, BohmanWeightingFunction },
    { Triangle,  1.0, 1.0, 0.0, 0.0, TriangleWeightingFunction },
    { Lagrange,  2.0, 1.0, 0.0, 0.0, LagrangeWeightingFunction },
    { SincFast,  3.0, 1.0, 0.0, 0.0, SincFastWeightingFunction },
    { SincFast,  3.0, 1.0, 0.0, 0.0, SincFastWeightingFunction },
    { SincFast,  2.0, 1.0, 0.0, 0.0, SincFastWeightingFunction },
    { SincFast,  2.0, 1.0, 0.0, 0.0, SincFastWeightingFunction },

    { CubicBC,   2.0, 1.1685777620836932,
                            0.37821575509399867, 0.31089212245300067, CubicBCWeightingFunction },

    { CubicBC,   2.0, 1.105822933719019,
                            0.2620145123990142,  0.3689927438004929, CubicBCWeightingFunction },
    { Cosine,    1.0, 1.0, 0.0, 0.0, CosineWeightingFunction },
    { CubicBC,   2.0, 2.0, 1.0, 0.0, CubicBCWeightingFunction },
    { SincFast,  3.0, 1.0, 0.0, 0.0, SincFastWeightingFunction },
    { CubicSpline,2.0, 0.5, 0.0, 0.0, BoxWeightingFunction },
  };


  static double
    jinc_zeros[16] =
    {
      1.2196698912665045,
      2.2331305943815286,
      3.2383154841662362,
      4.2410628637960699,
      5.2427643768701817,
      6.2439216898644877,
      7.2447598687199570,
      8.2453949139520427,
      9.2458926849494673,
      10.246293348754916,
      11.246622794877883,
      12.246898461138105,
      13.247132522181061,
      14.247333735806849,
      15.247508563037300,
      16.247661874700962
   };


  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  assert(UndefinedFilter < filter && filter < SentinelFilter);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  resize_filter=(ResizeFilter *) AcquireMagickMemory(sizeof(*resize_filter));
  if (resize_filter == (ResizeFilter *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  (void) ResetMagickMemory(resize_filter,0,sizeof(*resize_filter));


  filter_type=mapping[filter].filter;
  window_type=mapping[filter].window;
  resize_filter->blur=1.0;

  if ( cylindrical != MagickFalse && (filter_type == SincFastFilter) &&
      (filter != SincFastFilter))
    filter_type=JincFilter;


  artifact=GetImageArtifact(image,"filter:filter");
  if (IsStringTrue(artifact) != MagickFalse)
    {
      ssize_t
        option;

      option=ParseCommandOption(MagickFilterOptions,MagickFalse,artifact);
      if ((UndefinedFilter < option) && (option < SentinelFilter))
        {
          filter_type=(FilterType) option;
          window_type=BoxFilter;
        }

      artifact=GetImageArtifact(image,"filter:window");
      if (artifact != (const char *) NULL)
        {
          option=ParseCommandOption(MagickFilterOptions,MagickFalse,artifact);
          if ((UndefinedFilter < option) && (option < SentinelFilter))
            window_type=(FilterType) option;
        }
    }
  else
    {

      artifact=GetImageArtifact(image,"filter:window");
      if (artifact != (const char *) NULL)
        {
          ssize_t
            option;

          option=ParseCommandOption(MagickFilterOptions,MagickFalse,artifact);
          if ((UndefinedFilter < option) && (option < SentinelFilter))
            {
              filter_type= cylindrical != MagickFalse ? JincFilter
                                                     : SincFastFilter;
              window_type=(FilterType) option;
            }
        }
    }


  resize_filter->filter=filters[filter_type].function;
  resize_filter->support=filters[filter_type].support;
  resize_filter->filterWeightingType=filters[filter_type].weightingFunctionType;
  resize_filter->window=filters[window_type].function;
  resize_filter->windowWeightingType=filters[window_type].weightingFunctionType;
  resize_filter->scale=filters[window_type].scale;
  resize_filter->signature=MagickCoreSignature;


  if (cylindrical != MagickFalse)
    switch (filter_type)
    {
      case BoxFilter:

        resize_filter->support=(double) MagickSQ1_2;
        break;
      case LanczosFilter:
      case LanczosSharpFilter:
      case Lanczos2Filter:
      case Lanczos2SharpFilter:
      case LanczosRadiusFilter:
        resize_filter->filter=filters[JincFilter].function;
        resize_filter->window=filters[JincFilter].function;
        resize_filter->scale=filters[JincFilter].scale;

        break;
      default:
        break;
    }

  switch (filter_type)
  {
    case LanczosSharpFilter:
      resize_filter->blur *= 0.9812505644269356;
      break;
    case Lanczos2SharpFilter:
      resize_filter->blur *= 0.9549963639785485;
      break;

    default:
      break;
  }


  if ((resize_filter->filter == Gaussian) ||
      (resize_filter->window == Gaussian) ) {
    value=0.5;
    artifact=GetImageArtifact(image,"filter:sigma");
    if (artifact != (const char *) NULL)
      value=StringToDouble(artifact,(char **) NULL);

    resize_filter->coefficient[0]=value;
    resize_filter->coefficient[1]=PerceptibleReciprocal(2.0*value*value);
    resize_filter->coefficient[2]=PerceptibleReciprocal(Magick2PI*value*value);

    if ( value > 0.5 )
      resize_filter->support *= 2*value;
  }


  if ((resize_filter->filter == Kaiser) ||
      (resize_filter->window == Kaiser) ) {
    value=6.5;
    artifact=GetImageArtifact(image,"filter:alpha");
    if (artifact != (const char *) NULL)
      value=StringToDouble(artifact,(char **) NULL);
    artifact=GetImageArtifact(image,"filter:kaiser-beta");
    if (artifact != (const char *) NULL)
      value=StringToDouble(artifact,(char **) NULL);
    artifact=GetImageArtifact(image,"filter:kaiser-alpha");
    if (artifact != (const char *) NULL)
      value=StringToDouble(artifact,(char **) NULL)*MagickPI;

    resize_filter->coefficient[0]=value;
    resize_filter->coefficient[1]=PerceptibleReciprocal(I0(value));

  }


  artifact=GetImageArtifact(image,"filter:lobes");
  if (artifact != (const char *) NULL)
    {
      ssize_t
        lobes;

      lobes=(ssize_t) StringToLong(artifact);
      if (lobes < 1)
        lobes=1;
      resize_filter->support=(double) lobes;
    }
  if (resize_filter->filter == Jinc)
    {


      if (resize_filter->support > 16)
        resize_filter->support=jinc_zeros[15];
      else
        resize_filter->support=jinc_zeros[((long) resize_filter->support)-1];


      if (filter_type == LanczosRadiusFilter)
        resize_filter->blur*=floor(resize_filter->support)/
          resize_filter->support;
    }


  artifact=GetImageArtifact(image,"filter:blur");
  if (artifact != (const char *) NULL)
    resize_filter->blur*=StringToDouble(artifact,(char **) NULL);
  if (resize_filter->blur < MagickEpsilon)
    resize_filter->blur=(double) MagickEpsilon;


  artifact=GetImageArtifact(image,"filter:support");
  if (artifact != (const char *) NULL)
    resize_filter->support=fabs(StringToDouble(artifact,(char **) NULL));


  resize_filter->window_support=resize_filter->support;
  artifact=GetImageArtifact(image,"filter:win-support");
  if (artifact != (const char *) NULL)
    resize_filter->window_support=fabs(StringToDouble(artifact,(char **) NULL));


  resize_filter->scale/=resize_filter->window_support;


  B=0.0;
  C=0.0;
  if ((resize_filter->filter == CubicBC) ||
      (resize_filter->window == CubicBC) )
    {
      B=filters[filter_type].B;
      C=filters[filter_type].C;
      if (filters[window_type].function == CubicBC)
        {
          B=filters[window_type].B;
          C=filters[window_type].C;
        }
      artifact=GetImageArtifact(image,"filter:b");
      if (artifact != (const char *) NULL)
        {
          B=StringToDouble(artifact,(char **) NULL);
          C=(1.0-B)/2.0;
          artifact=GetImageArtifact(image,"filter:c");
          if (artifact != (const char *) NULL)
            C=StringToDouble(artifact,(char **) NULL);
        }
      else
        {
          artifact=GetImageArtifact(image,"filter:c");
          if (artifact != (const char *) NULL)
            {
              C=StringToDouble(artifact,(char **) NULL);
              B=1.0-2.0*C;
            }
        }
      {
        const double
          twoB = B+B;


        resize_filter->coefficient[0]=1.0-(1.0/3.0)*B;
        resize_filter->coefficient[1]=-3.0+twoB+C;
        resize_filter->coefficient[2]=2.0-1.5*B-C;
        resize_filter->coefficient[3]=(4.0/3.0)*B+4.0*C;
        resize_filter->coefficient[4]=-8.0*C-twoB;
        resize_filter->coefficient[5]=B+5.0*C;
        resize_filter->coefficient[6]=(-1.0/6.0)*B-C;
      }
    }


#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp master
  {
#endif
    if (IsStringTrue(GetImageArtifact(image,"filter:verbose")) != MagickFalse)
      {
        double
          support,
          x;


        if (resize_filter->filter == Box)       filter_type=BoxFilter;
        if (resize_filter->filter == Sinc)      filter_type=SincFilter;
        if (resize_filter->filter == SincFast)  filter_type=SincFastFilter;
        if (resize_filter->filter == Jinc)      filter_type=JincFilter;
        if (resize_filter->filter == CubicBC)   filter_type=CubicFilter;
        if (resize_filter->window == Box)       window_type=BoxFilter;
        if (resize_filter->window == Sinc)      window_type=SincFilter;
        if (resize_filter->window == SincFast)  window_type=SincFastFilter;
        if (resize_filter->window == Jinc)      window_type=JincFilter;
        if (resize_filter->window == CubicBC)   window_type=CubicFilter;


        support=GetResizeFilterSupport(resize_filter);
        (void) FormatLocaleFile(stdout,
          "# Resampling Filter (for graphing)\n#\n");
        (void) FormatLocaleFile(stdout,"# filter = %s\n",
          CommandOptionToMnemonic(MagickFilterOptions,filter_type));
        (void) FormatLocaleFile(stdout,"# window = %s\n",
          CommandOptionToMnemonic(MagickFilterOptions,window_type));
        (void) FormatLocaleFile(stdout,"# support = %.*g\n",
          GetMagickPrecision(),(double) resize_filter->support);
        (void) FormatLocaleFile(stdout,"# window-support = %.*g\n",
          GetMagickPrecision(),(double) resize_filter->window_support);
        (void) FormatLocaleFile(stdout,"# scale-blur = %.*g\n",
          GetMagickPrecision(),(double)resize_filter->blur);
        if ((filter_type == GaussianFilter) || (window_type == GaussianFilter))
          (void) FormatLocaleFile(stdout,"# gaussian-sigma = %.*g\n",
            GetMagickPrecision(),(double)resize_filter->coefficient[0]);
        if ( filter_type == KaiserFilter || window_type == KaiserFilter )
          (void) FormatLocaleFile(stdout,"# kaiser-beta = %.*g\n",
            GetMagickPrecision(),(double)resize_filter->coefficient[0]);
        (void) FormatLocaleFile(stdout,"# practical-support = %.*g\n",
          GetMagickPrecision(), (double)support);
        if ( filter_type == CubicFilter || window_type == CubicFilter )
          (void) FormatLocaleFile(stdout,"# B,C = %.*g,%.*g\n",
            GetMagickPrecision(),(double)B, GetMagickPrecision(),(double)C);
        (void) FormatLocaleFile(stdout,"\n");


        for (x=0.0; x <= support; x+=0.01f)
          (void) FormatLocaleFile(stdout,"%5.2lf\t%.*g\n",x,
            GetMagickPrecision(),(double)
            GetResizeFilterWeight(resize_filter,x));


        (void) FormatLocaleFile(stdout,"%5.2lf\t%.*g\n",support,
          GetMagickPrecision(),0.0);
      }

    (void) DeleteImageArtifact((Image *) image,"filter:verbose");
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  }
#endif
  return(resize_filter);
}
