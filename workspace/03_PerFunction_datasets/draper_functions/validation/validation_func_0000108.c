LogToFile(int buffer, enum tSeverityLevel SeverityLvl, const char *FunctionName, char *Format, ...)
{
  va_list argp;
  time_t t;
  struct tm *tm;
  char *s1, *s2;
  size_t i, j;
  char line_to_log[MAX_LOG_LINE_LENGTH];
  char temp_buffer[MAX_LOG_LINE_LENGTH];


  if( (Logfp == NULL) && (buffer == 0) )
  {
    return 1;
  }

  va_start(argp, Format);
  pal_vsnprintf(line_to_log, sizeof(line_to_log), Format, argp);
  va_end(argp);


  t = pal_time(NULL);
  if( t == (time_t)-1 )
  {
    return 1;
  }

  tm = pal_localtime(&t);
  if( tm == NULL )
  {
    return 1;
  }

  i = pal_strlen(line_to_log);
  s1 = s2 = malloc(i + 1);

  if( s1 == NULL )
  {
    return 1;
  }


  for( j = 0;j < i; j++ )
  {
    if( line_to_log[j] != '\r' && line_to_log[j] != '\n' )
    {
      *s1++ = line_to_log[j];
    }
  }

  *s1++ = '\0';


  pal_snprintf(temp_buffer,
    sizeof(temp_buffer),
#if defined(_DEBUG) || defined(DEBUG)
    "%04d/%02d/%02d %02d:%02d:%02d %c %s: %s: %s\n",
#else
    "%04d/%02d/%02d %02d:%02d:%02d %c %s: %s\n",
#endif
    (tm->tm_year+1900),
    (tm->tm_mon+1),
    tm->tm_mday,
    tm->tm_hour,
    tm->tm_min,
    tm->tm_sec,
    SeverityToChar( SeverityLvl ),
    LogConfiguration->identity == NULL ? "" : LogConfiguration->identity,
#if defined(_DEBUG) || defined(DEBUG)
    FunctionName == NULL ? "" : FunctionName,
#endif
    s2 );

  free(s2);


  if( buffer != 0 )
  {


    buffer_append(&LogBuffer, (void *)temp_buffer, pal_strlen(temp_buffer) + 1);
  }
  else
  {

    if( LogConfiguration->log_rotation == TRUE )
    {
      if( RotateLogFile(LogConfiguration->log_filename, LogConfiguration->log_rotation_size, temp_buffer) != 0 )
      {
      }
    }


    if( fprintf(Logfp, "%s", temp_buffer) < 0 )
    {
      return 1;
    }


    if( fflush(Logfp) != 0 )
    {
      return 1;
    }
  }

  return 0;
}
