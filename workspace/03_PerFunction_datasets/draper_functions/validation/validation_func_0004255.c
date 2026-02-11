_maskhost(const char *s, char *nw, int host)
{
  register const char *p, *q, *e, *f;
  int i;

  *nw++ = '*';
  *nw++ = '!';
  p = (q = strchr(s, '!')) ? q + 1 : s;

  if ((q = strchr(p, '@'))) {
    int fl = 0;

    if ((q - p) > 9) {
      nw[0] = '*';
      p = q - 7;
      i = 1;
    } else
      i = 0;
    while (*p != '@') {
      if (!fl && strchr("~+-^=", *p)) {
        if (strict_host)
          nw[i] = '?';
        else if (!host)
          nw[i] = '*';
        else
          i--;
      } else
        nw[i] = *p;
      fl++;
      p++;
      i++;
    }
    nw[i++] = '@';
    q++;
  } else {
    nw[0] = '*';
    nw[1] = '@';
    i = 2;
    q = s;
  }
  nw += i;
  e = NULL;

  if ((!(p = strchr(q, '.')) || !(e = strchr(p + 1, '.'))) && !strchr(q, ':'))

    strcpy(nw, q);
  else {
    if (e == NULL) {
      const char *mask_str;

      f = strrchr(q, ':');
      if (strchr(f, '.')) {
        f = strrchr(f, '.');
        mask_str = ".*";
      } else
        mask_str = ":*";
      strncpy(nw, q, f - q);


      nw += (f - q);
      strcpy(nw, mask_str);
    } else {
      for (f = e; *f; f++);
      f--;
      if (*f >= '0' && *f <= '9') {
        while (*f != '.')
          f--;
        strncpy(nw, q, f - q);


        nw += (f - q);
        strcpy(nw, ".*");
      } else {


        const char *x = strchr(e + 1, '.');

        if (!x)
          x = p;
        else if (strchr(x + 1, '.'))
          x = e;
        else if (strlen(x) == 3)
          x = p;
        else
          x = e;
        sprintf(nw, "*%s", x);
      }
    }
  }
}
