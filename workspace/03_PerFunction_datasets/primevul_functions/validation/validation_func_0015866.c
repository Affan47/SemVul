MagickExport void SetResampleFilter(ResampleFilter *resample_filter,
  const FilterType filter)
{
  ResizeFilter
     *resize_filter;

  assert(resample_filter != (ResampleFilter *) NULL);
  assert(resample_filter->signature == MagickCoreSignature);

  resample_filter->do_interpolate = MagickFalse;
  resample_filter->filter = filter;


  if ( filter == UndefinedFilter )
    resample_filter->filter = RobidouxFilter;

  if ( resample_filter->filter == PointFilter ) {
    resample_filter->do_interpolate = MagickTrue;
    return;
  }

  resize_filter = AcquireResizeFilter(resample_filter->image,
    resample_filter->filter,MagickTrue,resample_filter->exception);
  if (resize_filter == (ResizeFilter *) NULL) {
    (void) ThrowMagickException(resample_filter->exception,GetMagickModule(),
         ModuleError, "UnableToSetFilteringValue",
         "Fall back to Interpolated 'Point' filter");
    resample_filter->filter = PointFilter;
    resample_filter->do_interpolate = MagickTrue;
    return;
  }


#if EWA
  resample_filter->support = GetResizeFilterSupport(resize_filter);
#else
  resample_filter->support = 2.0;
#endif

#if FILTER_LUT

  { int
       Q;
    double
       r_scale;


    r_scale = resample_filter->support*sqrt(1.0/(double)WLUT_WIDTH);
    for(Q=0; Q<WLUT_WIDTH; Q++)
      resample_filter->filter_lut[Q] = (double)
           GetResizeFilterWeight(resize_filter,sqrt((double)Q)*r_scale);


    resize_filter = DestroyResizeFilter(resize_filter);
  }
#else

  resample_filter->filter_def = resize_filter;
  resample_filter->F = resample_filter->support*resample_filter->support;
#endif


  ScaleResampleFilter(resample_filter, 1.0, 0.0, 0.0, 1.0);

#if 0


  r_scale = -2.77258872223978123767/(WLUT_WIDTH*blur*blur);
  for(Q=0; Q<WLUT_WIDTH; Q++)
    resample_filter->filter_lut[Q] = exp((double)Q*r_scale);
  resample_filter->support = WLUT_WIDTH;
#endif

#if FILTER_LUT
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp single
#endif
  {
    if (IsStringTrue(GetImageArtifact(resample_filter->image,
        "resample:verbose")) != MagickFalse)
      {
        int
          Q;
        double
          r_scale;


        printf("#\n");
        printf("# Resampling Filter LUT (%d values) for '%s' filter\n",
                   WLUT_WIDTH, CommandOptionToMnemonic(MagickFilterOptions,
                   resample_filter->filter) );
        printf("#\n");
        printf("# Note: values in table are using a squared radius lookup.\n");
        printf("# As such its distribution is not uniform.\n");
        printf("#\n");
        printf("# The X value is the support distance for the Y weight\n");
        printf("# so you can use gnuplot to plot this cylindrical filter\n");
        printf("#    plot [0:2][-.2:1] \"lut.dat\" with lines\n");
        printf("#\n");


        r_scale = resample_filter->support*sqrt(1.0/(double)WLUT_WIDTH);
        for(Q=0; Q<WLUT_WIDTH; Q++)
          printf("%8.*g %.*g\n",
              GetMagickPrecision(),sqrt((double)Q)*r_scale,
              GetMagickPrecision(),resample_filter->filter_lut[Q] );
        printf("\n\n");
      }


  }
#endif
  return;
}
