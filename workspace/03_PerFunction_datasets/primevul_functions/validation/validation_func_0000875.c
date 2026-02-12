static const char *GetMagickPropertyLetter(const ImageInfo *image_info,
  Image *image,const char letter)
{
  char
    value[MaxTextExtent];

  const char
    *string;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  *value='\0';
  string=(char *) NULL;
  switch (letter)
  {
    case 'b':
    {


      (void) FormatMagickSize(image->extent,MagickFalse,value);
      if (image->extent == 0)
        (void) FormatMagickSize(GetBlobSize(image),MagickFalse,value);
      break;
    }
    case 'c':
    {


      string=GetImageProperty(image,"comment");
      if (string == (const char *) NULL)
        string="";
      break;
    }
    case 'd':
    {


      GetPathComponent(image->magick_filename,HeadPath,value);
      if (*value == '\0')
        string="";
      break;
    }
    case 'e':
    {


      GetPathComponent(image->magick_filename,ExtensionPath,value);
      if (*value == '\0')
        string="";
      break;
    }
    case 'f':
    {


      GetPathComponent(image->magick_filename,TailPath,value);
      if (*value == '\0')
        string="";
      break;
    }
    case 'g':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20gx%.20g%+.20g%+.20g",
        (double) image->page.width,(double) image->page.height,
        (double) image->page.x,(double) image->page.y);
      break;
    }
    case 'h':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        (image->rows != 0 ? image->rows : image->magick_rows));
      break;
    }
    case 'i':
    {


      string=image->filename;
      break;
    }
    case 'k':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        GetNumberColors(image,(FILE *) NULL,&image->exception));
      break;
    }
    case 'l':
    {


      string=GetImageProperty(image,"label");
      if (string == (const char *) NULL)
        string="";
      break;
    }
    case 'm':
    {


      string=image->magick;
      break;
    }
    case 'n':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        GetImageListLength(image));
      break;
    }
    case 'o':
    {


      string=image_info->filename;
      break;
    }
    case 'p':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        GetImageIndexInList(image));
      break;
    }
    case 'q':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        MAGICKCORE_QUANTUM_DEPTH);
      break;
    }
    case 'r':
    {
      ColorspaceType
        colorspace;


      colorspace=image->colorspace;
      if ((image->columns != 0) && (image->rows != 0) &&
          (SetImageGray(image,&image->exception) != MagickFalse))
        colorspace=GRAYColorspace;
      (void) FormatLocaleString(value,MaxTextExtent,"%s %s %s",
        CommandOptionToMnemonic(MagickClassOptions,(ssize_t)
        image->storage_class),CommandOptionToMnemonic(MagickColorspaceOptions,
        (ssize_t) colorspace),image->matte != MagickFalse ? "Matte" : "" );
      break;
    }
    case 's':
    {


      if (image_info->number_scenes != 0)
        (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
          image_info->scene);
      else
        (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
          image->scene);
      break;
    }
    case 't':
    {


      GetPathComponent(image->magick_filename,BasePath,value);
      break;
    }
    case 'u':
    {


      string=image_info->unique;
      break;
    }
    case 'w':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        (image->columns != 0 ? image->columns : image->magick_columns));
      break;
    }
    case 'x':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",
        fabs(image->x_resolution) > MagickEpsilon ? image->x_resolution : 72.0);
      break;
    }
    case 'y':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",
        fabs(image->y_resolution) > MagickEpsilon ? image->y_resolution : 72.0);
      break;
    }
    case 'z':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        image->depth);
      break;
    }
    case 'A':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%s",
         CommandOptionToMnemonic(MagickBooleanOptions,(ssize_t) image->matte));
      break;
    }
    case 'B':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        image->extent);
      if (image->extent == 0)
        (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
          GetBlobSize(image));
      break;
    }
    case 'C':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%s",
        CommandOptionToMnemonic(MagickCompressOptions,(ssize_t)
          image->compression));
      break;
    }
    case 'D':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%s",
        CommandOptionToMnemonic(MagickDisposeOptions,(ssize_t) image->dispose));
      break;
    }
    case 'F':
    {
      const char
        *q;

      register char
        *p;

      static char
        whitelist[] =
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 "
          "$-_.+!*'(),{}|\\^~[]`\"><#%;/?:@&=";


      (void) CopyMagickString(value,image->magick_filename,MaxTextExtent);
      p=value;
      q=value+strlen(value);
      for (p+=strspn(p,whitelist); p != q; p+=strspn(p,whitelist))
        *p='_';
      break;
    }
    case 'G':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20gx%.20g",(double)
        image->magick_columns,(double) image->magick_rows);
      break;
    }
    case 'H':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        image->page.height);
      break;
    }
    case 'M':
    {


      string=image->magick_filename;
      break;
    }
    case 'O':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%+ld%+ld",(long)
        image->page.x,(long) image->page.y);
      break;
    }
    case 'P':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20gx%.20g",(double)
        image->page.width,(double) image->page.height);
      break;
    }
    case 'Q':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        (image->quality == 0 ? 92 : image->quality));
      break;
    }
    case 'S':
    {


      if (image_info->number_scenes == 0)
        string="2147483647";
      else
        (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
          image_info->scene+image_info->number_scenes);
      break;
    }
    case 'T':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        image->delay);
      break;
    }
    case 'U':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%s",
        CommandOptionToMnemonic(MagickResolutionOptions,(ssize_t)
          image->units));
      break;
    }
    case 'W':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%.20g",(double)
        image->page.width);
      break;
    }
    case 'X':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%+.20g",(double)
        image->page.x);
      break;
    }
    case 'Y':
    {


      (void) FormatLocaleString(value,MaxTextExtent,"%+.20g",(double)
        image->page.y);
      break;
    }
    case 'Z':
    {


      string=image_info->zero;
      break;
    }
    case '@':
    {
      RectangleInfo
        page;


      page=GetImageBoundingBox(image,&image->exception);
      (void) FormatLocaleString(value,MaxTextExtent,"%.20gx%.20g%+.20g%+.20g",
        (double) page.width,(double) page.height,(double) page.x,(double)
        page.y);
      break;
    }
    case '#':
    {


      if ((image->columns != 0) && (image->rows != 0))
        (void) SignatureImage(image);
      string=GetImageProperty(image,"signature");
      break;
    }
    case '%':
    {


      string="%";
      break;
    }
  }
  if (*value != '\0')
    string=value;
  if (string != (char *) NULL)
    {
      (void) SetImageArtifact(image,"get-property",string);
      return(GetImageArtifact(image,"get-property"));
    }
  return((char *) NULL);
}
