MagickExport void ScaleResampleFilter(ResampleFilter *resample_filter,
  const double dux,const double duy,const double dvx,const double dvy)
{
  double A,B,C,F;

  assert(resample_filter != (ResampleFilter *) NULL);
  assert(resample_filter->signature == MagickCoreSignature);

  resample_filter->limit_reached = MagickFalse;


  if ( resample_filter->filter == PointFilter )
    return;

#if DEBUG_ELLIPSE
  (void) FormatLocaleFile(stderr, "# -----\n" );
  (void) FormatLocaleFile(stderr, "dux=%lf; dvx=%lf;   duy=%lf; dvy=%lf;\n",
       dux, dvx, duy, dvy);
#endif


#if EWA


#if EWA_CLAMP
  { double major_mag,
           minor_mag,
           major_x,
           major_y,
           minor_x,
           minor_y;

  ClampUpAxes(dux,dvx,duy,dvy, &major_mag, &minor_mag,
                &major_x, &major_y, &minor_x, &minor_y);
  major_x *= major_mag;  major_y *= major_mag;
  minor_x *= minor_mag;  minor_y *= minor_mag;
#if DEBUG_ELLIPSE
  (void) FormatLocaleFile(stderr, "major_x=%lf; major_y=%lf;  minor_x=%lf; minor_y=%lf;\n",
        major_x, major_y, minor_x, minor_y);
#endif
  A = major_y*major_y+minor_y*minor_y;
  B = -2.0*(major_x*major_y+minor_x*minor_y);
  C = major_x*major_x+minor_x*minor_x;
  F = major_mag*minor_mag;
  F *= F;
  }
#else
  A = dvx*dvx+dvy*dvy;
  B = -2.0*(dux*dvx+duy*dvy);
  C = dux*dux+duy*duy;
  F = dux*dvy-duy*dvx;
  F *= F;
#endif

#else


  A = dvx*dvx+dvy*dvy+1;
  B = -2.0*(dux*dvx+duy*dvy);
  C = dux*dux+duy*duy+1;
  F = A*C - B*B/4;
#endif

#if DEBUG_ELLIPSE
  (void) FormatLocaleFile(stderr, "A=%lf; B=%lf; C=%lf; F=%lf\n", A,B,C,F);


  { double alpha, beta, gamma, Major, Minor;
    double Eccentricity, Ellipse_Area, Ellipse_Angle;

    alpha = A+C;
    beta  = A-C;
    gamma = sqrt(beta*beta + B*B );

    if ( alpha - gamma <= MagickEpsilon )
      Major=MagickMaximumValue;
    else
      Major=sqrt(2*F/(alpha - gamma));
    Minor = sqrt(2*F/(alpha + gamma));

    (void) FormatLocaleFile(stderr, "# Major=%lf; Minor=%lf\n", Major, Minor );


    Eccentricity = Major/Minor;
    Ellipse_Area = MagickPI*Major*Minor;
    Ellipse_Angle = atan2(B, A-C);

    (void) FormatLocaleFile(stderr, "# Angle=%lf   Area=%lf\n",
         (double) RadiansToDegrees(Ellipse_Angle), Ellipse_Area);
  }
#endif


  if ( (4*A*C - B*B) > MagickMaximumValue ) {
    resample_filter->limit_reached = MagickTrue;
    return;
  }


  F *= resample_filter->support;
  F *= resample_filter->support;


  resample_filter->Ulimit = sqrt(C*F/(A*C-0.25*B*B));
  resample_filter->Vlimit = sqrt(A*F/(A*C-0.25*B*B));


  resample_filter->Uwidth = sqrt(F/A);
  resample_filter->slope = -B/(2.0*A);

#if DEBUG_ELLIPSE
  (void) FormatLocaleFile(stderr, "Ulimit=%lf; Vlimit=%lf; UWidth=%lf; Slope=%lf;\n",
           resample_filter->Ulimit, resample_filter->Vlimit,
           resample_filter->Uwidth, resample_filter->slope );
#endif


  if ( (resample_filter->Uwidth * resample_filter->Vlimit)
         > (4.0*resample_filter->image_area)) {
    resample_filter->limit_reached = MagickTrue;
    return;
  }


  { double scale;
#if FILTER_LUT

    scale=(double) WLUT_WIDTH*PerceptibleReciprocal(F);
#else

    scale=resample_filter->F*PerceptibleReciprocal(F);
#endif
    resample_filter->A = A*scale;
    resample_filter->B = B*scale;
    resample_filter->C = C*scale;
  }
}
