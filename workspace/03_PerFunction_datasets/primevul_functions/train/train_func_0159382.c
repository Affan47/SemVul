static double *GenerateCoefficients(const Image *image,
  DistortImageMethod *method,const size_t number_arguments,
  const double *arguments,size_t number_values,ExceptionInfo *exception)
{
  double
    *coeff;

  size_t
    i;

  size_t
    number_coeff,
    cp_size,
    cp_x,cp_y,
    cp_values;


  if ( number_values == 0 ) {


    number_values = 2;
    cp_values = 0;
    cp_x = 2;
    cp_y = 3;

  }
  else {
    cp_x = 0;
    cp_y = 1;
    cp_values = 2;

  }
  cp_size = number_values+2;


  if ( number_arguments < 4*cp_size &&
       (  *method == BilinearForwardDistortion
       || *method == BilinearReverseDistortion
       || *method == PerspectiveDistortion
       ) )
    *method = AffineDistortion;

  number_coeff=0;
  switch (*method) {
    case AffineDistortion:

      number_coeff=3*number_values;
      break;
    case PolynomialDistortion:

      i = poly_number_terms(arguments[0]);
      number_coeff = 2 + i*number_values;
      if ( i == 0 ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
                   "InvalidArgument","%s : '%s'","Polynomial",
                   "Invalid order, should be interger 1 to 5, or 1.5");
        return((double *) NULL);
      }
      if ( number_arguments < 1+i*cp_size ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
               "InvalidArgument", "%s : 'require at least %.20g CPs'",
               "Polynomial", (double) i);
        return((double *) NULL);
      }
      break;
    case BilinearReverseDistortion:
      number_coeff=4*number_values;
      break;


    case BilinearForwardDistortion:
      number_coeff=10;
      cp_x = 0;
      cp_y = 1;
      cp_values = 2;
      break;
#if 0
    case QuadraterialDistortion:
      number_coeff=19;
#endif
      break;
    case ShepardsDistortion:
      number_coeff=1;
      break;
    case ArcDistortion:
      number_coeff=5;
      break;
    case ScaleRotateTranslateDistortion:
    case AffineProjectionDistortion:
    case Plane2CylinderDistortion:
    case Cylinder2PlaneDistortion:
      number_coeff=6;
      break;
    case PolarDistortion:
    case DePolarDistortion:
      number_coeff=8;
      break;
    case PerspectiveDistortion:
    case PerspectiveProjectionDistortion:
      number_coeff=9;
      break;
    case BarrelDistortion:
    case BarrelInverseDistortion:
      number_coeff=10;
      break;
    default:
      perror("unknown method given");
  }


  coeff = (double *) AcquireQuantumMemory(number_coeff,sizeof(*coeff));
  if (coeff == (double *) NULL) {
    (void) ThrowMagickException(exception,GetMagickModule(),
                  ResourceLimitError,"MemoryAllocationFailed",
                  "%s", "GenerateCoefficients");
    return((double *) NULL);
  }


  for (i=0; i < number_coeff; i++)
    coeff[i] = 0.0;

  switch (*method)
  {
    case AffineDistortion:
    {


      if ( number_arguments%cp_size != 0 ||
           number_arguments < cp_size ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
               "InvalidArgument", "%s : 'require at least %.20g CPs'",
               "Affine", 1.0);
        coeff=(double *) RelinquishMagickMemory(coeff);
        return((double *) NULL);
      }

      if ( number_arguments == cp_size ) {

        if ( cp_values == 0 ) {

          coeff[0] = 1.0;
          coeff[2] = arguments[0] - arguments[2];
          coeff[4] = 1.0;
          coeff[5] = arguments[1] - arguments[3];
        }
        else {

          for (i=0; i<number_values; i++)
            coeff[i*3+2] = arguments[cp_values+i];
        }
      }
      else {


        double
          **matrix,
          **vectors,
          terms[3];

        MagickBooleanType
          status;


        matrix = AcquireMagickMatrix(3UL,3UL);
        vectors = (double **) AcquireQuantumMemory(number_values,sizeof(*vectors));
        if (matrix == (double **) NULL || vectors == (double **) NULL)
        {
          matrix  = RelinquishMagickMatrix(matrix, 3UL);
          vectors = (double **) RelinquishMagickMemory(vectors);
          coeff   = (double *) RelinquishMagickMemory(coeff);
          (void) ThrowMagickException(exception,GetMagickModule(),
                  ResourceLimitError,"MemoryAllocationFailed",
                  "%s", "DistortCoefficients");
          return((double *) NULL);
        }

        for (i=0; i < number_values; i++)
          vectors[i] = &(coeff[i*3]);

        for (i=0; i < number_arguments; i+=cp_size) {
          terms[0] = arguments[i+cp_x];
          terms[1] = arguments[i+cp_y];
          terms[2] = 1;
          LeastSquaresAddTerms(matrix,vectors,terms,
                   &(arguments[i+cp_values]),3UL,number_values);
        }
        if ( number_arguments == 2*cp_size ) {


          terms[0] = arguments[cp_x]
                   - ( arguments[cp_size+cp_y] - arguments[cp_y] );
          terms[1] = arguments[cp_y] +
                   + ( arguments[cp_size+cp_x] - arguments[cp_x] );
          terms[2] = 1;
          if ( cp_values == 0 ) {

            double
              uv2[2];
            uv2[0] = arguments[0] - arguments[5] + arguments[1];
            uv2[1] = arguments[1] + arguments[4] - arguments[0];
            LeastSquaresAddTerms(matrix,vectors,terms,uv2,3UL,2UL);
          }
          else {

            LeastSquaresAddTerms(matrix,vectors,terms,
                  &(arguments[cp_values]),3UL,number_values);
          }
        }

        status=GaussJordanElimination(matrix,vectors,3UL,number_values);
        matrix = RelinquishMagickMatrix(matrix, 3UL);
        vectors = (double **) RelinquishMagickMemory(vectors);
        if ( status == MagickFalse ) {
          coeff = (double *) RelinquishMagickMemory(coeff);
          (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument","%s : 'Unsolvable Matrix'",
              CommandOptionToMnemonic(MagickDistortOptions, *method) );
          return((double *) NULL);
        }
      }
      return(coeff);
    }
    case AffineProjectionDistortion:
    {


      double inverse[8];
      if (number_arguments != 6) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument","%s : 'Needs 6 coeff values'",
              CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      }

      for(i=0; i<6UL; i++ )
        inverse[i] = arguments[i];
      AffineArgsToCoefficients(inverse);
      InvertAffineCoefficients(inverse, coeff);
      *method = AffineDistortion;

      return(coeff);
    }
    case ScaleRotateTranslateDistortion:
    {


      double
        cosine, sine,
        x,y,sx,sy,a,nx,ny;


      x = nx = (double)(image->columns)/2.0 + (double)image->page.x;
      y = ny = (double)(image->rows)/2.0    + (double)image->page.y;
      sx = sy = 1.0;
      switch ( number_arguments ) {
      case 0:
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument","%s : 'Needs at least 1 argument'",
              CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      case 1:
        a = arguments[0];
        break;
      case 2:
        sx = sy = arguments[0];
        a = arguments[1];
        break;
      default:
        x = nx = arguments[0];
        y = ny = arguments[1];
        switch ( number_arguments ) {
        case 3:
          a = arguments[2];
          break;
        case 4:
          sx = sy = arguments[2];
          a = arguments[3];
          break;
        case 5:
          sx = arguments[2];
          sy = arguments[3];
          a = arguments[4];
          break;
        case 6:
          sx = sy = arguments[2];
          a = arguments[3];
          nx = arguments[4];
          ny = arguments[5];
          break;
        case 7:
          sx = arguments[2];
          sy = arguments[3];
          a = arguments[4];
          nx = arguments[5];
          ny = arguments[6];
          break;
        default:
          coeff = (double *) RelinquishMagickMemory(coeff);
          (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument","%s : 'Too Many Arguments (7 or less)'",
              CommandOptionToMnemonic(MagickDistortOptions, *method) );
          return((double *) NULL);
        }
        break;
      }

      if ( fabs(sx) < MagickEpsilon || fabs(sy) < MagickEpsilon ) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument","%s : 'Zero Scale Given'",
              CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      }

      a=DegreesToRadians(a); cosine=cos(a); sine=sin(a);

      *method = AffineDistortion;
      coeff[0]=cosine/sx;
      coeff[1]=sine/sx;
      coeff[2]=x-nx*coeff[0]-ny*coeff[1];
      coeff[3]=(-sine)/sy;
      coeff[4]=cosine/sy;
      coeff[5]=y-nx*coeff[3]-ny*coeff[4];
      return(coeff);
    }
    case PerspectiveDistortion:
    {


      double
        **matrix,
        *vectors[1],
        terms[8];

      size_t
        cp_u = cp_values,
        cp_v = cp_values+1;

      MagickBooleanType
        status;

      if ( number_arguments%cp_size != 0 ||
           number_arguments < cp_size*4 ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument", "%s : 'require at least %.20g CPs'",
              CommandOptionToMnemonic(MagickDistortOptions, *method), 4.0);
        coeff=(double *) RelinquishMagickMemory(coeff);
        return((double *) NULL);
      }

      vectors[0] = &(coeff[0]);

      matrix = AcquireMagickMatrix(8UL,8UL);
      if (matrix == (double **) NULL) {
        coeff=(double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),
                  ResourceLimitError,"MemoryAllocationFailed",
                  "%s", "DistortCoefficients");
        return((double *) NULL);
      }

      for (i=0; i < number_arguments; i+=4) {
        terms[0]=arguments[i+cp_x];
        terms[1]=arguments[i+cp_y];
        terms[2]=1.0;
        terms[3]=0.0;
        terms[4]=0.0;
        terms[5]=0.0;
        terms[6]=-terms[0]*arguments[i+cp_u];
        terms[7]=-terms[1]*arguments[i+cp_u];
        LeastSquaresAddTerms(matrix,vectors,terms,&(arguments[i+cp_u]),
            8UL,1UL);

        terms[0]=0.0;
        terms[1]=0.0;
        terms[2]=0.0;
        terms[3]=arguments[i+cp_x];
        terms[4]=arguments[i+cp_y];
        terms[5]=1.0;
        terms[6]=-terms[3]*arguments[i+cp_v];
        terms[7]=-terms[4]*arguments[i+cp_v];
        LeastSquaresAddTerms(matrix,vectors,terms,&(arguments[i+cp_v]),
            8UL,1UL);
      }

      status=GaussJordanElimination(matrix,vectors,8UL,1UL);
      matrix = RelinquishMagickMatrix(matrix, 8UL);
      if ( status == MagickFalse ) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
            "InvalidArgument","%s : 'Unsolvable Matrix'",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      }


      coeff[8] = coeff[6]*arguments[cp_x]
                      + coeff[7]*arguments[cp_y] + 1.0;
      coeff[8] = (coeff[8] < 0.0) ? -1.0 : +1.0;

      return(coeff);
    }
    case PerspectiveProjectionDistortion:
    {


      if (number_arguments != 8) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument", "%s : 'Needs 8 coefficient values'",
              CommandOptionToMnemonic(MagickDistortOptions, *method));
        return((double *) NULL);
      }

      InvertPerspectiveCoefficients(arguments, coeff);


      coeff[8] = coeff[6]*arguments[2]
                           + coeff[7]*arguments[5] + 1.0;
      coeff[8] = (coeff[8] < 0.0) ? -1.0 : +1.0;
      *method = PerspectiveDistortion;

      return(coeff);
    }
    case BilinearForwardDistortion:
    case BilinearReverseDistortion:
    {


      double
        **matrix,
        **vectors,
        terms[4];

      MagickBooleanType
        status;


      if ( number_arguments%cp_size != 0 ||
           number_arguments < cp_size*4 ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument", "%s : 'require at least %.20g CPs'",
              CommandOptionToMnemonic(MagickDistortOptions, *method), 4.0);
        coeff=(double *) RelinquishMagickMemory(coeff);
        return((double *) NULL);
      }

      matrix = AcquireMagickMatrix(4UL,4UL);
      vectors = (double **) AcquireQuantumMemory(number_values,sizeof(*vectors));
      if (matrix == (double **) NULL || vectors == (double **) NULL)
      {
        matrix  = RelinquishMagickMatrix(matrix, 4UL);
        vectors = (double **) RelinquishMagickMemory(vectors);
        coeff   = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),
                ResourceLimitError,"MemoryAllocationFailed",
                "%s", "DistortCoefficients");
        return((double *) NULL);
      }

      for (i=0; i < number_values; i++)
        vectors[i] = &(coeff[i*4]);

      for (i=0; i < number_arguments; i+=cp_size) {
        terms[0] = arguments[i+cp_x];
        terms[1] = arguments[i+cp_y];
        terms[2] = terms[0]*terms[1];
        terms[3] = 1;
        LeastSquaresAddTerms(matrix,vectors,terms,
             &(arguments[i+cp_values]),4UL,number_values);
      }

      status=GaussJordanElimination(matrix,vectors,4UL,number_values);
      matrix  = RelinquishMagickMatrix(matrix, 4UL);
      vectors = (double **) RelinquishMagickMemory(vectors);
      if ( status == MagickFalse ) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
            "InvalidArgument","%s : 'Unsolvable Matrix'",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      }
      if ( *method == BilinearForwardDistortion ) {


         coeff[8] = coeff[0]*coeff[5] - coeff[1]*coeff[4];
         coeff[9] = 2*(coeff[2]*coeff[5] - coeff[1]*coeff[6]);
      }
      return(coeff);
    }
#if 0
    case QuadrilateralDistortion:
    {


      return(coeff);
    }
#endif

    case PolynomialDistortion:
    {


      double
        **matrix,
        **vectors,
        *terms;

      size_t
        nterms;

      ssize_t
        j;

      MagickBooleanType
        status;


      coeff[0] = arguments[0];
      coeff[1] = (double) poly_number_terms(arguments[0]);
      nterms = (size_t) coeff[1];


      matrix = AcquireMagickMatrix(nterms,nterms);
      vectors = (double **) AcquireQuantumMemory(number_values,sizeof(*vectors));
      terms = (double *) AcquireQuantumMemory(nterms, sizeof(*terms));
      if (matrix  == (double **) NULL ||
          vectors == (double **) NULL ||
          terms   == (double *) NULL )
      {
        matrix  = RelinquishMagickMatrix(matrix, nterms);
        vectors = (double **) RelinquishMagickMemory(vectors);
        terms   = (double *) RelinquishMagickMemory(terms);
        coeff   = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),
                ResourceLimitError,"MemoryAllocationFailed",
                "%s", "DistortCoefficients");
        return((double *) NULL);
      }

      for (i=0; i < number_values; i++)
        vectors[i] = &(coeff[2+i*nterms]);

      for (i=1; i < number_arguments; i+=cp_size) {
        for (j=0; j < (ssize_t) nterms; j++)
          terms[j] = poly_basis_fn(j,arguments[i+cp_x],arguments[i+cp_y]);
        LeastSquaresAddTerms(matrix,vectors,terms,
             &(arguments[i+cp_values]),nterms,number_values);
      }
      terms = (double *) RelinquishMagickMemory(terms);

      status=GaussJordanElimination(matrix,vectors,nterms,number_values);
      matrix  = RelinquishMagickMatrix(matrix, nterms);
      vectors = (double **) RelinquishMagickMemory(vectors);
      if ( status == MagickFalse ) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
            "InvalidArgument","%s : 'Unsolvable Matrix'",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      }
      return(coeff);
    }
    case ArcDistortion:
    {


      if ( number_arguments >= 1 && arguments[0] < MagickEpsilon ) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
            "InvalidArgument","%s : 'Arc Angle Too Small'",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      }
      if ( number_arguments >= 3 && arguments[2] < MagickEpsilon ) {
        coeff = (double *) RelinquishMagickMemory(coeff);
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
            "InvalidArgument","%s : 'Outer Radius Too Small'",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        return((double *) NULL);
      }
      coeff[0] = -MagickPI2;
      if ( number_arguments >= 1 )
        coeff[1] = DegreesToRadians(arguments[0]);
      else
        coeff[1] = MagickPI2;
      if ( number_arguments >= 2 )
        coeff[0] += DegreesToRadians(arguments[1]);
      coeff[0] /= Magick2PI;
      coeff[0] -= MagickRound(coeff[0]);
      coeff[0] *= Magick2PI;
      coeff[3] = (double)image->rows-1;
      coeff[2] = (double)image->columns/coeff[1] + coeff[3]/2.0;
      if ( number_arguments >= 3 ) {
        if ( number_arguments >= 4 )
          coeff[3] = arguments[2] - arguments[3];
        else
          coeff[3] *= arguments[2]/coeff[2];
        coeff[2] = arguments[2];
      }
      coeff[4] = ((double)image->columns-1.0)/2.0;

      return(coeff);
    }
    case PolarDistortion:
    case DePolarDistortion:
    {


      if ( number_arguments == 3
          || ( number_arguments > 6 && *method == PolarDistortion )
          || number_arguments > 8 ) {
          (void) ThrowMagickException(exception,GetMagickModule(),
            OptionError,"InvalidArgument", "%s : number of arguments",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        coeff=(double *) RelinquishMagickMemory(coeff);
        return((double *) NULL);
      }

      if ( number_arguments >= 1 )
        coeff[0] = arguments[0];
      else
        coeff[0] = 0.0;

      coeff[1] = number_arguments >= 2 ? arguments[1] : 0.0;

      if ( number_arguments >= 4 ) {
        coeff[2] = arguments[2];
        coeff[3] = arguments[3];
      }
      else {
        coeff[2] = (double)(image->columns)/2.0+image->page.x;
        coeff[3] = (double)(image->rows)/2.0+image->page.y;
      }

      coeff[4] = -MagickPI;
      if ( number_arguments >= 5 )
        coeff[4] = DegreesToRadians(arguments[4]);
      coeff[5] = coeff[4];
      if ( number_arguments >= 6 )
        coeff[5] = DegreesToRadians(arguments[5]);
      if ( fabs(coeff[4]-coeff[5]) < MagickEpsilon )
        coeff[5] += Magick2PI;

      if ( coeff[0] < MagickEpsilon ) {

        if ( fabs(coeff[0]) < MagickEpsilon ) {
          coeff[0]=MagickMin(fabs(coeff[2]-image->page.x),
                             fabs(coeff[3]-image->page.y));
          coeff[0]=MagickMin(coeff[0],
                       fabs(coeff[2]-image->page.x-image->columns));
          coeff[0]=MagickMin(coeff[0],
                       fabs(coeff[3]-image->page.y-image->rows));
        }

        if ( fabs(-1.0-coeff[0]) < MagickEpsilon ) {
          double rx,ry;
          rx = coeff[2]-image->page.x;
          ry = coeff[3]-image->page.y;
          coeff[0] = rx*rx+ry*ry;
          ry = coeff[3]-image->page.y-image->rows;
          coeff[0] = MagickMax(coeff[0],rx*rx+ry*ry);
          rx = coeff[2]-image->page.x-image->columns;
          coeff[0] = MagickMax(coeff[0],rx*rx+ry*ry);
          ry = coeff[3]-image->page.y;
          coeff[0] = MagickMax(coeff[0],rx*rx+ry*ry);
          coeff[0] = sqrt(coeff[0]);
        }
      }

      if ( coeff[0] < MagickEpsilon || coeff[1] < -MagickEpsilon
           || (coeff[0]-coeff[1]) < MagickEpsilon ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
            "InvalidArgument", "%s : Invalid Radius",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        coeff=(double *) RelinquishMagickMemory(coeff);
        return((double *) NULL);
      }

      if ( *method == PolarDistortion ) {
        coeff[6]=(double) image->columns/(coeff[5]-coeff[4]);
        coeff[7]=(double) image->rows/(coeff[0]-coeff[1]);
      }
      else {
        coeff[6]=(coeff[5]-coeff[4])/image->columns;
        coeff[7]=(coeff[0]-coeff[1])/image->rows;
      }
      return(coeff);
    }
    case Cylinder2PlaneDistortion:
    case Plane2CylinderDistortion:
    {


      if ( arguments[0] < MagickEpsilon || arguments[0] > 160.0 ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
            "InvalidArgument", "%s : Invalid FOV Angle",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
        coeff=(double *) RelinquishMagickMemory(coeff);
        return((double *) NULL);
      }
      coeff[0] = DegreesToRadians(arguments[0]);
      if ( *method == Cylinder2PlaneDistortion )


        coeff[1] = (double) image->columns/coeff[0];
      else

        coeff[1] = (double) image->columns / ( 2 * tan(coeff[0]/2) );

      coeff[2] = (double)(image->columns)/2.0+image->page.x;
      coeff[3] = (double)(image->rows)/2.0+image->page.y;
      coeff[4] = coeff[2];
      coeff[5] = coeff[3];
      return(coeff);
    }
    case BarrelDistortion:
    case BarrelInverseDistortion:
    {


      double
        rscale = 2.0/MagickMin((double) image->columns,(double) image->rows);


      if ( (number_arguments  < 3) || (number_arguments == 7) ||
           (number_arguments == 9) || (number_arguments > 10) )
        {
          coeff=(double *) RelinquishMagickMemory(coeff);
          (void) ThrowMagickException(exception,GetMagickModule(),
            OptionError,"InvalidArgument", "%s : number of arguments",
            CommandOptionToMnemonic(MagickDistortOptions, *method) );
          return((double *) NULL);
        }

      coeff[0] = arguments[0];
      coeff[1] = arguments[1];
      coeff[2] = arguments[2];
      if ((number_arguments == 3) || (number_arguments == 5) )
        coeff[3] = 1.0 - coeff[0] - coeff[1] - coeff[2];
      else
        coeff[3] = arguments[3];

      coeff[0] *= pow(rscale,3.0);
      coeff[1] *= rscale*rscale;
      coeff[2] *= rscale;

      if ( number_arguments >= 8 ) {
        coeff[4] = arguments[4] * pow(rscale,3.0);
        coeff[5] = arguments[5] * rscale*rscale;
        coeff[6] = arguments[6] * rscale;
        coeff[7] = arguments[7];
      }
      else {
        coeff[4] = coeff[0];
        coeff[5] = coeff[1];
        coeff[6] = coeff[2];
        coeff[7] = coeff[3];
      }

      if ( number_arguments == 5 )  {
        coeff[8] = arguments[3];
        coeff[9] = arguments[4];
      }
      else if ( number_arguments == 6 ) {
        coeff[8] = arguments[4];
        coeff[9] = arguments[5];
      }
      else if ( number_arguments == 10 ) {
        coeff[8] = arguments[8];
        coeff[9] = arguments[9];
      }
      else {

        coeff[8] = (double)image->columns/2.0 + image->page.x;
        coeff[9] = (double)image->rows/2.0    + image->page.y;
      }
      return(coeff);
    }
    case ShepardsDistortion:
    {


      if ( number_arguments%cp_size != 0 ||
           number_arguments < cp_size ) {
        (void) ThrowMagickException(exception,GetMagickModule(),OptionError,
              "InvalidArgument", "%s : 'requires CP's (4 numbers each)'",
              CommandOptionToMnemonic(MagickDistortOptions, *method));
        coeff=(double *) RelinquishMagickMemory(coeff);
        return((double *) NULL);
      }

      { const char *artifact=GetImageArtifact(image,"shepards:power");
        if ( artifact != (const char *) NULL ) {
          coeff[0]=StringToDouble(artifact,(char **) NULL) / 2.0;
          if ( coeff[0] < MagickEpsilon ) {
            (void) ThrowMagickException(exception,GetMagickModule(),
                OptionError,"InvalidArgument","%s", "-define shepards:power" );
            coeff=(double *) RelinquishMagickMemory(coeff);
            return((double *) NULL);
          }
        }
        else
          coeff[0]=1.0;
      }
      return(coeff);
    }
    default:
      break;
  }

  perror("no method handler");
  return((double *) NULL);
}
