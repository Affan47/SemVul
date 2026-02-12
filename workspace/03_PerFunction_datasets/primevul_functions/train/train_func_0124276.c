string_vformat(gstring * g, BOOL extend, const char *format, va_list ap)
{
enum ltypes { L_NORMAL=1, L_SHORT=2, L_LONG=3, L_LONGLONG=4, L_LONGDOUBLE=5, L_SIZE=6 };

int width, precision, off, lim;
const char * fp = format;

string_datestamp_offset = -1;
string_datestamp_length = 0;
string_datestamp_type = 0;

#ifdef COMPILE_UTILITY
assert(!extend);
assert(g);
#else


if (!g) g = string_get(16);
#endif

lim = g->size - 1;
off = g->ptr;


while (*fp)
  {
  int length = L_NORMAL;
  int *nptr;
  int slen;
  const char *null = "NULL";
  const char *item_start, *s;
  char newformat[16];
  char * gp = CS g->s + g->ptr;


  if (*fp != '%')
    {

    if (g->ptr >= lim - 1)
      {
      if (!extend) return NULL;
      gstring_grow(g, g->ptr, 1);
      lim = g->size - 1;
      }
    g->s[g->ptr++] = (uschar) *fp++;
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
    if (*(++fp) == '*')
      {
      precision = va_arg(ap, int);
      fp++;
      }
    else
      for (precision = 0; isdigit((uschar)*fp); fp++)
        precision = precision*10 + *fp - '0';


  if (*fp == 'h')
    { fp++; length = L_SHORT; }
  else if (*fp == 'L')
    { fp++; length = L_LONGDOUBLE; }
  else if (*fp == 'l')
    if (fp[1] == 'l')
      { fp += 2; length = L_LONGLONG; }
    else
      { fp++; length = L_LONG; }
  else if (*fp == 'z')
    { fp++; length = L_SIZE; }


  switch (*fp++)
    {
    case 'n':
      nptr = va_arg(ap, int *);
      *nptr = g->ptr - off;
      break;

    case 'd':
    case 'o':
    case 'u':
    case 'x':
    case 'X':
      width = length > L_LONG ? 24 : 12;
      if (g->ptr >= lim - width)
	{
	if (!extend) return NULL;
	gstring_grow(g, g->ptr, width);
	lim = g->size - 1;
	gp = CS g->s + g->ptr;
	}
      strncpy(newformat, item_start, fp - item_start);
      newformat[fp - item_start] = 0;


      switch(length)
	{
	case L_SHORT:
	case L_NORMAL:
	  g->ptr += sprintf(gp, newformat, va_arg(ap, int)); break;
	case L_LONG:
	  g->ptr += sprintf(gp, newformat, va_arg(ap, long int)); break;
	case L_LONGLONG:
	  g->ptr += sprintf(gp, newformat, va_arg(ap, LONGLONG_T)); break;
	case L_SIZE:
	  g->ptr += sprintf(gp, newformat, va_arg(ap, size_t)); break;
	}
      break;

    case 'p':
      {
      void * ptr;
      if (g->ptr >= lim - 24)
	{
	if (!extend) return NULL;
	gstring_grow(g, g->ptr, 24);
	lim = g->size - 1;
	gp = CS g->s + g->ptr;
	}


      if ((ptr = va_arg(ap, void *)))
	{
	strncpy(newformat, item_start, fp - item_start);
	newformat[fp - item_start] = 0;
	g->ptr += sprintf(gp, newformat, ptr);
	}
      else
	g->ptr += sprintf(gp, "(nil)");
      }
    break;


    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      if (precision < 0) precision = 6;
      if (g->ptr >= lim - precision - 8)
	{
	if (!extend) return NULL;
	gstring_grow(g, g->ptr, precision+8);
	lim = g->size - 1;
	gp = CS g->s + g->ptr;
	}
      strncpy(newformat, item_start, fp - item_start);
      newformat[fp-item_start] = 0;
      if (length == L_LONGDOUBLE)
	g->ptr += sprintf(gp, newformat, va_arg(ap, long double));
      else
	g->ptr += sprintf(gp, newformat, va_arg(ap, double));
      break;


    case '%':
      if (g->ptr >= lim - 1)
	{
	if (!extend) return NULL;
	gstring_grow(g, g->ptr, 1);
	lim = g->size - 1;
	}
      g->s[g->ptr++] = (uschar) '%';
      break;

    case 'c':
      if (g->ptr >= lim - 1)
	{
	if (!extend) return NULL;
	gstring_grow(g, g->ptr, 1);
	lim = g->size - 1;
	}
      g->s[g->ptr++] = (uschar) va_arg(ap, int);
      break;

    case 'D':
      s = CS tod_stamp(tod_log_datestamp_daily);
      string_datestamp_offset = g->ptr;
      string_datestamp_length = Ustrlen(s);
      string_datestamp_type = tod_log_datestamp_daily;
      slen = string_datestamp_length;
      goto INSERT_STRING;

    case 'M':
      s = CS tod_stamp(tod_log_datestamp_monthly);
      string_datestamp_offset = g->ptr;
      string_datestamp_length = Ustrlen(s);
      string_datestamp_type = tod_log_datestamp_monthly;
      slen = string_datestamp_length;
      goto INSERT_STRING;

    case 's':
    case 'S':
    case 'T':
      s = va_arg(ap, char *);

      if (!s) s = null;
      slen = Ustrlen(s);

    INSERT_STRING:

      {
      BOOL truncated = FALSE;


      if (width >= 0)
	{
	if (precision < 0) precision = width;
	}


      else if (precision >= 0)
	width = precision < slen ? precision : slen;


      else
	width = precision = slen;

      if (!extend)
	{
	if (g->ptr == lim) return NULL;
	if (g->ptr >= lim - width)
	  {
	  truncated = TRUE;
	  width = precision = lim - g->ptr - 1;
	  if (width < 0) width = 0;
	  if (precision < 0) precision = 0;
	  }
	}
      else if (g->ptr >= lim - width)
	{
	gstring_grow(g, g->ptr, width);
	lim = g->size - 1;
	gp = CS g->s + g->ptr;
	}

      g->ptr += sprintf(gp, "%*.*s", width, precision, s);
      if (fp[-1] == 'S')
	while (*gp) { *gp = tolower(*gp); gp++; }
      else if (fp[-1] == 'T')
	while (*gp) { *gp = toupper(*gp); gp++; }

      if (truncated) return NULL;
      break;
      }


    default:
      strncpy(newformat, item_start, fp - item_start);
      newformat[fp-item_start] = 0;
      log_write(0, LOG_MAIN|LOG_PANIC_DIE, "string_format: unsupported type "
	"in \"%s\" in \"%s\"", newformat, format);
      break;
    }
  }

return g;
}
