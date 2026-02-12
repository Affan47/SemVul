string_vformat(uschar *buffer, int buflen, char *format, va_list ap)
{
enum { L_NORMAL, L_SHORT, L_LONG, L_LONGLONG, L_LONGDOUBLE };

BOOL yield = TRUE;
int width, precision;
char *fp = format;
uschar *p = buffer;
uschar *last = buffer + buflen - 1;

string_datestamp_offset = -1;


while (*fp != 0)
  {
  int length = L_NORMAL;
  int *nptr;
  int slen;
  char *null = "NULL";
  char *item_start, *s;
  char newformat[16];


  if (*fp != '%')
    {
    if (p >= last) { yield = FALSE; break; }
    *p++ = (uschar)*fp++;
    continue;
    }


  item_start = fp;
  width = precision = -1;

  if (strchr("-+ #0", *(++fp)) != NULL)
    {
    if (*fp == '#') null = "";
    fp++;
    }

  if (isdigit((uschar)*fp))
    {
    width = *fp++ - '0';
    while (isdigit((uschar)*fp)) width = width * 10 + *fp++ - '0';
    }
  else if (*fp == '*')
    {
    width = va_arg(ap, int);
    fp++;
    }

  if (*fp == '.')
    {
    if (*(++fp) == '*')
      {
      precision = va_arg(ap, int);
      fp++;
      }
    else
      {
      precision = 0;
      while (isdigit((uschar)*fp))
        precision = precision*10 + *fp++ - '0';
      }
    }


  if (*fp == 'h')
    { fp++; length = L_SHORT; }
  else if (*fp == 'L')
    { fp++; length = L_LONGDOUBLE; }
  else if (*fp == 'l')
    {
    if (fp[1] == 'l')
      {
      fp += 2;
      length = L_LONGLONG;
      }
    else
      {
      fp++;
      length = L_LONG;
      }
    }


  switch (*fp++)
    {
    case 'n':
    nptr = va_arg(ap, int *);
    *nptr = p - buffer;
    break;

    case 'd':
    case 'o':
    case 'u':
    case 'x':
    case 'X':
    if (p >= last - ((length > L_LONG)? 24 : 12))
      { yield = FALSE; goto END_FORMAT; }
    strncpy(newformat, item_start, fp - item_start);
    newformat[fp - item_start] = 0;


    switch(length)
      {
      case L_SHORT:
      case L_NORMAL:   sprintf(CS p, newformat, va_arg(ap, int)); break;
      case L_LONG:     sprintf(CS p, newformat, va_arg(ap, long int)); break;
      case L_LONGLONG: sprintf(CS p, newformat, va_arg(ap, LONGLONG_T)); break;
      }
    while (*p) p++;
    break;

    case 'p':
    if (p >= last - 24) { yield = FALSE; goto END_FORMAT; }
    strncpy(newformat, item_start, fp - item_start);
    newformat[fp - item_start] = 0;
    sprintf(CS p, newformat, va_arg(ap, void *));
    while (*p) p++;
    break;


    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    if (precision < 0) precision = 6;
    if (p >= last - precision - 8) { yield = FALSE; goto END_FORMAT; }
    strncpy(newformat, item_start, fp - item_start);
    newformat[fp-item_start] = 0;
    if (length == L_LONGDOUBLE)
      sprintf(CS p, newformat, va_arg(ap, long double));
    else
      sprintf(CS p, newformat, va_arg(ap, double));
    while (*p) p++;
    break;


    case '%':
    if (p >= last) { yield = FALSE; goto END_FORMAT; }
    *p++ = '%';
    break;

    case 'c':
    if (p >= last) { yield = FALSE; goto END_FORMAT; }
    *p++ = va_arg(ap, int);
    break;

    case 'D':
    s = CS tod_stamp(tod_log_datestamp);
    string_datestamp_offset = p - buffer;
    goto INSERT_STRING;

    case 's':
    case 'S':
    s = va_arg(ap, char *);

    INSERT_STRING:
    if (s == NULL) s = null;
    slen = Ustrlen(s);


    if (width >= 0)
      {
      if (precision < 0) precision = width;
      }


    else if (precision >= 0)
      {
      width = (precision < slen)? precision : slen;
      }


    else width = precision = slen;


    if (p == last)
      {
      yield = FALSE;
      goto END_FORMAT;
      }
    if (p >= last - width)
      {
      yield = FALSE;
      width = precision = last - p - 1;
      if (width < 0) width = 0;
      if (precision < 0) precision = 0;
      }
    sprintf(CS p, "%*.*s", width, precision, s);
    if (fp[-1] == 'S')
      while (*p) { *p = tolower(*p); p++; }
    else
      while (*p) p++;
    if (!yield) goto END_FORMAT;
    break;


    default:
    strncpy(newformat, item_start, fp - item_start);
    newformat[fp-item_start] = 0;
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "string_format: unsupported type "
      "in \"%s\" in \"%s\"", newformat, format);
    break;
    }
  }


END_FORMAT:

*p = 0;
return yield;
}
