MagickExport char *InterpretImageProperties(const ImageInfo *image_info,
  Image *image,const char *embed_text)
{
#define ExtendInterpretText(string_length) \
DisableMSCWarning(4127) \
{ \
  size_t length=(string_length); \
  if ((size_t) (q-interpret_text+length+1) >= extent) \
    { \
      extent+=length; \
      interpret_text=(char *) ResizeQuantumMemory(interpret_text,extent+ \
        MaxTextExtent,sizeof(*interpret_text)); \
      if (interpret_text == (char *) NULL) \
        { \
          if (property_info != image_info) \
            property_info=DestroyImageInfo(property_info); \
          return((char *) NULL); \
        } \
      q=interpret_text+strlen(interpret_text); \
   } \
} \
RestoreMSCWarning

#define AppendKeyValue2Text(key,value)\
DisableMSCWarning(4127) \
{ \
  size_t length=strlen(key)+strlen(value)+2; \
  if ((size_t) (q-interpret_text+length+1) >= extent) \
    { \
      extent+=length; \
      interpret_text=(char *) ResizeQuantumMemory(interpret_text,extent+ \
        MaxTextExtent,sizeof(*interpret_text)); \
      if (interpret_text == (char *) NULL) \
        { \
          if (property_info != image_info) \
            property_info=DestroyImageInfo(property_info); \
          return((char *) NULL); \
        } \
      q=interpret_text+strlen(interpret_text); \
     } \
   q+=FormatLocaleString(q,extent,"%s=%s\n",(key),(value)); \
} \
RestoreMSCWarning

#define AppendString2Text(string) \
DisableMSCWarning(4127) \
{ \
  size_t length=strlen((string)); \
  if ((size_t) (q-interpret_text+length+1) >= extent) \
    { \
      extent+=length; \
      interpret_text=(char *) ResizeQuantumMemory(interpret_text,extent+ \
        MaxTextExtent,sizeof(*interpret_text)); \
      if (interpret_text == (char *) NULL) \
        { \
          if (property_info != image_info) \
            property_info=DestroyImageInfo(property_info); \
          return((char *) NULL); \
        } \
      q=interpret_text+strlen(interpret_text); \
    } \
  (void) CopyMagickString(q,(string),extent); \
  q+=length; \
} \
RestoreMSCWarning

  char
    *interpret_text;

  ImageInfo
    *property_info;

  register char
    *q;

  register const char
    *p;

  size_t
    extent;

  MagickBooleanType
    number;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  if (embed_text == (const char *) NULL)
    return(ConstantString(""));
  p=embed_text;
  while ((isspace((int) ((unsigned char) *p)) != 0) && (*p != '\0'))
    p++;
  if (*p == '\0')
    return(ConstantString(""));
  if ((*p == '@') && (IsPathAccessible(p+1) != MagickFalse))
    {


      if (IsRightsAuthorized(PathPolicyDomain,ReadPolicyRights,p) == MagickFalse)
        {
          errno=EPERM;
          (void) ThrowMagickException(&image->exception,GetMagickModule(),
            PolicyError,"NotAuthorized","`%s'",p);
          return(ConstantString(""));
        }
      interpret_text=FileToString(p+1,~0UL,&image->exception);
      if (interpret_text != (char *) NULL)
        return(interpret_text);
    }


  if (image_info != (ImageInfo *) NULL)
    property_info=(ImageInfo *) image_info;
  else
    property_info=CloneImageInfo(image_info);
  interpret_text=AcquireString(embed_text);
  extent=MaxTextExtent;
  number=MagickFalse;
  for (q=interpret_text; *p!='\0';
    number=(isdigit((int) ((unsigned char) *p))) ? MagickTrue : MagickFalse,p++)
  {


    *q='\0';
    ExtendInterpretText(MaxTextExtent);
    switch (*p)
    {
      case '\\':
      {
        switch (*(p+1))
        {
          case '\0':
            continue;
          case 'r':
          {
            *q++='\r';
            p++;
            continue;
          }
          case 'n':
          {
            *q++='\n';
            p++;
            continue;
          }
          case '\n':
          {
            p++;
            continue;
          }
          case '\r':
          {
            p++;
            if (*p == '\n')
              p++;
            continue;
          }
          default:
          {
            p++;
            *q++=(*p);
          }
        }
        continue;
      }
      case '&':
      {
        if (LocaleNCompare("&lt;",p,4) == 0)
          {
            *q++='<';
             p+=3;
          }
        else
          if (LocaleNCompare("&gt;",p,4) == 0)
            {
              *q++='>';
               p+=3;
            }
          else
            if (LocaleNCompare("&amp;",p,5) == 0)
              {
                *q++='&';
                p+=4;
              }
            else
              *q++=(*p);
        continue;
      }
      case '%':
        break;
      default:
      {
        *q++=(*p);
        continue;
      }
    }
    p++;


    if ((*p == '\0') || (*p == '\'') || (*p == '"'))
      p--;
    if (*p == '%')
      {
        *q++='%';
        continue;
      }


    if (*p != '[')
      {
        const char
          *value;


        if (number != MagickFalse)
          {
            *q++='%';
            p--;
            continue;
          }
        value=GetMagickPropertyLetter(property_info,image,*p);
        if (value != (char *) NULL)
          {
            AppendString2Text(value);
            continue;
          }
        (void) ThrowMagickException(&image->exception,GetMagickModule(),
          OptionWarning,"UnknownImageProperty","\"%%%c\"",*p);
        continue;
      }
    {
      char
        pattern[2*MaxTextExtent];

      const char
        *key,
        *value;

      register ssize_t
        len;

      ssize_t
        depth;


      p++;
      depth=1;
      if ( *p == ']' )
        {
          (void) ThrowMagickException(&image->exception,GetMagickModule(),
            OptionWarning,"UnknownImageProperty","\"%%[]\"");
          break;
        }
      for (len=0; len<(MaxTextExtent-1L) && (*p != '\0');)
      {
        if ((*p == '\\') && (*(p+1) != '\0'))
          {


            pattern[len++]=(*p++);
            pattern[len++]=(*p++);
            continue;
          }
        if (*p == '[')
          depth++;
        if (*p == ']')
          depth--;
        if (depth <= 0)
          break;
        pattern[len++]=(*p++);
      }
      pattern[len]='\0';
      if (depth != 0)
        {


          if (len >= 64)
            {
              pattern[61] = '.';
              pattern[62] = '.';
              pattern[63] = '.';
              pattern[64] = '\0';
            }
          (void) ThrowMagickException(&image->exception,GetMagickModule(),
            OptionError,"UnbalancedBraces","\"%%[%s\"",pattern);
          interpret_text=DestroyString(interpret_text);
          if (property_info != image_info)
            property_info=DestroyImageInfo(property_info);
          return((char *) NULL);
        }


      if (LocaleNCompare("fx:",pattern,3) == 0)
        {
          double
            value;

          FxInfo
            *fx_info;

          MagickBooleanType
            status;


          fx_info=AcquireFxInfo(image,pattern+3);
          status=FxEvaluateChannelExpression(fx_info,DefaultChannels,0,0,&value,
            &image->exception);
          fx_info=DestroyFxInfo(fx_info);
          if (status != MagickFalse)
            {
              char
                result[MagickPathExtent];

              (void) FormatLocaleString(result,MagickPathExtent,"%.*g",
                GetMagickPrecision(),(double) value);
              AppendString2Text(result);
            }
          continue;
        }
      if (LocaleNCompare("option:",pattern,7) == 0)
        {


          if (IsGlob(pattern+7) != MagickFalse)
            {
              ResetImageOptionIterator(property_info);
              while ((key=GetNextImageOption(property_info)) != (const char *) NULL)
              if (GlobExpression(key,pattern+7,MagickTrue) != MagickFalse)
                {
                  value=GetImageOption(property_info,key);
                  if (value != (const char *) NULL)
                    AppendKeyValue2Text(key,value);

                }
              continue;
            }
          value=GetImageOption(property_info,pattern+7);
          if (value != (char *) NULL)
            AppendString2Text(value);

          continue;
        }
      if (LocaleNCompare("artifact:",pattern,9) == 0)
        {


          if (IsGlob(pattern+9) != MagickFalse)
            {
              ResetImageArtifactIterator(image);
              while ((key=GetNextImageArtifact(image)) != (const char *) NULL)
                if (GlobExpression(key,pattern+9,MagickTrue) != MagickFalse)
                  {
                    value=GetImageArtifact(image,key);
                    if (value != (const char *) NULL)
                      AppendKeyValue2Text(key,value);

                  }
              continue;
            }
          value=GetImageArtifact(image,pattern+9);
          if (value != (char *) NULL)
            AppendString2Text(value);

          continue;
        }


      value=GetImageProperty(image,pattern);
      if (value != (const char *) NULL)
        {
          AppendString2Text(value);
          continue;
        }


      if (IsGlob(pattern) != MagickFalse)
        {
          ResetImagePropertyIterator(image);
          while ((key=GetNextImageProperty(image)) != (const char *) NULL)
            if (GlobExpression(key,pattern,MagickTrue) != MagickFalse)
              {
                value=GetImageProperty(image,key);
                if (value != (const char *) NULL)
                  AppendKeyValue2Text(key,value);

              }
          continue;
        }


      value=GetMagickProperty(property_info,image,pattern);
      if (value != (const char *) NULL)
        {
          AppendString2Text(value);
          continue;
        }


      value=GetImageArtifact(image,pattern);
      if (value != (char *) NULL)
        {
          AppendString2Text(value);
          continue;
        }


      value=GetImageOption(property_info,pattern);
      if (value != (char *) NULL)
        {
          AppendString2Text(value);
          continue;
        }


      if (len >= 64)
        {
          pattern[61] = '.';
          pattern[62] = '.';
          pattern[63] = '.';
          pattern[64] = '\0';
        }
      (void) ThrowMagickException(&image->exception,GetMagickModule(),
        OptionWarning,"UnknownImageProperty","\"%%[%s]\"",pattern);

    }
  }
  *q='\0';
  if (property_info != image_info)
    property_info=DestroyImageInfo(property_info);
  return(interpret_text);
}
