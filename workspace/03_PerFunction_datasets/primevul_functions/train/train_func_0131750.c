MagickExport MagickStatusType ParseGeometry(const char *geometry,
  GeometryInfo *geometry_info)
{
  char
    *p,
    pedantic_geometry[MagickPathExtent],
    *q;

  double
    value;

  GeometryInfo
    coordinate;

  int
    c;

  MagickStatusType
    flags;


  assert(geometry_info != (GeometryInfo *) NULL);
  (void) memset(geometry_info,0,sizeof(*geometry_info));
  flags=NoValue;
  if ((geometry == (char *) NULL) || (*geometry == '\0'))
    return(flags);
  if (strlen(geometry) >= (MagickPathExtent-1))
    return(flags);
  c=sscanf(geometry,"%lf%*[ ,]%lf%*[ ,]%lf%*[ ,]%lf",&coordinate.rho,
    &coordinate.sigma,&coordinate.xi,&coordinate.psi);
  if (c == 4)
    {


      geometry_info->rho=coordinate.rho;
      geometry_info->sigma=coordinate.sigma;
      geometry_info->xi=coordinate.xi;
      geometry_info->psi=coordinate.psi;
      flags|=RhoValue | SigmaValue | XiValue | PsiValue;
      return(flags);
    }
  (void) CopyMagickString(pedantic_geometry,geometry,MagickPathExtent);
  for (p=pedantic_geometry; *p != '\0'; )
  {
    c=(int) ((unsigned char) *p);
    if (isspace(c) != 0)
      {
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        continue;
      }
    switch (c)
    {
      case '%':
      {
        flags|=PercentValue;
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        break;
      }
      case '!':
      {
        flags|=AspectValue;
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        break;
      }
      case '<':
      {
        flags|=LessValue;
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        break;
      }
      case '>':
      {
        flags|=GreaterValue;
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        break;
      }
      case '^':
      {
        flags|=MinimumValue;
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        break;
      }
      case '@':
      {
        flags|=AreaValue;
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        break;
      }
      case '(':
      case ')':
      {
        (void) CopyMagickString(p,p+1,MagickPathExtent);
        break;
      }
      case 'x':
      case 'X':
      {
        flags|=SeparatorValue;
        p++;
        break;
      }
      case '-':
      case '+':
      case ',':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '/':
      case 215:
      case 'e':
      case 'E':
      {
        p++;
        break;
      }
      case '.':
      {
        p++;
        flags|=DecimalValue;
        break;
      }
      case ':':
      {
        p++;
        flags|=AspectRatioValue;
        break;
      }
      default:
        return(NoValue);
    }
  }


  p=pedantic_geometry;
  if (*p == '\0')
    return(flags);
  q=p;
  value=StringToDouble(p,&q);
  if (LocaleNCompare(p,"0x",2) == 0)
    (void) strtol(p,&q,10);
  c=(int) ((unsigned char) *q);
  if ((c == 215) || (*q == 'x') || (*q == 'X') || (*q == ':') ||
      (*q == ',') || (*q == '/') || (*q =='\0'))
    {


      q=p;
      if (LocaleNCompare(p,"0x",2) == 0)
        value=(double) strtol(p,&p,10);
      else
        value=StringToDouble(p,&p);
      if (p != q)
        {
          flags|=RhoValue;
          geometry_info->rho=value;
        }
    }
  q=p;
  c=(int) ((unsigned char) *p);
  if ((c == 215) || (*p == 'x') || (*p == 'X') || (*p == ':') || (*p == ',') ||
      (*p == '/'))
    {


      p++;
      while (isspace((int) ((unsigned char) *p)) != 0)
        p++;
      c=(int) ((unsigned char) *q);
      if (((c != 215) && (*q != 'x') && (*q != 'X') && (*q != ':')) ||
          ((*p != '+') && (*p != '-')))
        {
          q=p;
          value=StringToDouble(p,&p);
          if (p != q)
            {
              flags|=SigmaValue;
              geometry_info->sigma=value;
            }
        }
    }
  while (isspace((int) ((unsigned char) *p)) != 0)
    p++;
  if ((*p == '+') || (*p == '-') || (*p == ',') || (*p == '/') || (*p == ':'))
    {


      if ((*p == ',') || (*p == '/') || (*p == ':') )
        p++;
      while ((*p == '+') || (*p == '-'))
      {
        if (*p == '-')
          flags^=XiNegative;
        p++;
      }
      q=p;
      value=StringToDouble(p,&p);
      if (p != q)
        {
          flags|=XiValue;
          if ((flags & XiNegative) != 0)
            value=(-value);
          geometry_info->xi=value;
        }
      while (isspace((int) ((unsigned char) *p)) != 0)
        p++;
      if ((*p == '+') || (*p == '-') || (*p == ',') || (*p == '/') ||
          (*p == ':'))
        {


          if ((*p == ',') || (*p == '/') || (*p == ':'))
            p++;
          while ((*p == '+') || (*p == '-'))
          {
            if (*p == '-')
              flags^=PsiNegative;
            p++;
          }
          q=p;
          value=StringToDouble(p,&p);
          if (p != q)
            {
              flags|=PsiValue;
              if ((flags & PsiNegative) != 0)
                value=(-value);
              geometry_info->psi=value;
            }
      }
      while (isspace((int) ((unsigned char) *p)) != 0)
        p++;
      if ((*p == '+') || (*p == '-') || (*p == ',') || (*p == '/') ||
          (*p == ':'))
        {


          if ((*p == ',') || (*p == '/') || (*p == ':'))
            p++;
          while ((*p == '+') || (*p == '-'))
          {
            if (*p == '-')
              flags^=ChiNegative;
            p++;
          }
          q=p;
          value=StringToDouble(p,&p);
          if (p != q)
            {
              flags|=ChiValue;
              if ((flags & ChiNegative) != 0)
                value=(-value);
              geometry_info->chi=value;
            }
        }
    }
  if (strchr(pedantic_geometry,':') != (char *) NULL)
    {


      if ((flags & SigmaValue) != 0)
        geometry_info->rho*=PerceptibleReciprocal(geometry_info->sigma);
      geometry_info->sigma=1.0;
      if (((flags & XiValue) != 0) && (geometry_info->xi == 0.0))
        geometry_info->sigma=2.0;
    }
  if (((flags & RhoValue) != 0) && ((flags & SigmaValue) == 0) &&
      ((flags & XiValue) != 0) && ((flags & XiNegative) != 0))
    {
      if ((flags & PsiValue) == 0)
        {


          geometry_info->sigma=geometry_info->xi;
          geometry_info->xi=0.0;
          flags|=SigmaValue;
          flags&=(~XiValue);
        }
      else
        if ((flags & ChiValue) == 0)
          {


            geometry_info->sigma=geometry_info->xi;
            geometry_info->xi=geometry_info->psi;
            flags|=SigmaValue;
            flags|=XiValue;
            flags&=(~PsiValue);
          }
        else
          {


            geometry_info->sigma=geometry_info->xi;
            geometry_info->xi=geometry_info->psi;
            geometry_info->psi=geometry_info->chi;
            flags|=SigmaValue;
            flags|=XiValue;
            flags|=PsiValue;
            flags&=(~ChiValue);
          }
    }
  if ((flags & PercentValue) != 0)
    {
      if (((flags & SeparatorValue) == 0) && ((flags & SigmaValue) == 0))
        geometry_info->sigma=geometry_info->rho;
      if (((flags & SeparatorValue) != 0) && ((flags & RhoValue) == 0))
        geometry_info->rho=geometry_info->sigma;
    }
#if 0

  (void) fprintf(stderr,"ParseGeometry...\n");
  (void) fprintf(stderr,"Flags: %c %c %s %s %s\n",
    (flags & RhoValue) ? 'W' : ' ',(flags & SigmaValue) ? 'H' : ' ',
    (flags & XiValue) ? ((flags & XiNegative) ? "-X" : "+X") : "  ",
    (flags & PsiValue) ? ((flags & PsiNegative) ? "-Y" : "+Y") : "  ",
    (flags & ChiValue) ? ((flags & ChiNegative) ? "-Z" : "+Z") : "  ");
  (void) fprintf(stderr,"Geometry: %lg,%lg,%lg,%lg,%lg\n",geometry_info->rho,
    geometry_info->sigma,geometry_info->xi,geometry_info->psi,
    geometry_info->chi);
#endif
  return(flags);
}
