msdosify (const char *file_name)
{
  static char dos_name[PATH_MAX];
  static const char illegal_chars_dos[] = ".+, ;=[]|<>\\\":?*";
  static const char *illegal_chars_w95 = &illegal_chars_dos[8];
  int idx, dot_idx;
  const char *s = file_name;
  char *d = dos_name;
  const char *illegal_aliens = illegal_chars_dos;
  size_t len = sizeof (illegal_chars_dos) - 1;
  int lfn = 0;

#ifdef DJGPP

  if (_use_lfn (file_name))
    lfn = 1;
#endif
  if (lfn) {
    illegal_aliens = illegal_chars_w95;
    len -= (illegal_chars_w95 - illegal_chars_dos);
  }


  if (s[0] >= 'A' && s[0] <= 'z' && s[1] == ':') {
    *d++ = *s++;
    *d++ = *s++;
  }

  for (idx = 0, dot_idx = -1; *s; s++, d++) {
    if (memchr (illegal_aliens, *s, len)) {


      if (*s == '.') {
        if (idx == 0 && (s[1] == '/' || (s[1] == '.' && s[2] == '/'))) {

          *d++ = *s++;
          if (*s == '.')
            *d++ = *s++;
          *d = *s;
        }
        else if (idx == 0)
          *d = '_';
        else if (dot_idx >= 0) {
          if (dot_idx < 5) {
            d[dot_idx - idx] = '_';
            *d = '.';
          }
          else
            *d = '-';
        }
        else
          *d = '.';

        if (*s == '.')
          dot_idx = idx;
      }
      else if (*s == '+' && s[1] == '+') {
        if (idx - 2 == dot_idx) {
          *d++ = 'x';
          *d   = 'x';
        }
        else {

          memcpy (d, "plus", 4);
          d += 3;
        }
        s++;
        idx++;
      }
      else
        *d = '_';
    }
    else
      *d = *s;
    if (*s == '/') {
      idx = 0;
      dot_idx = -1;
    }
    else
      idx++;
  }

  *d = '\0';
  return dos_name;
}
