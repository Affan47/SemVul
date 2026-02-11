compute_text_width (const a_fontdata *font, const char *text,
		    unsigned int *nspaces)
{
  unsigned int width = 0;
  unsigned int ns = 0;

  for (; *text; ++text) {
    if (*text == '%') {
      ++text;
      if (*text != '%')
	continue;
    }
    if (!nspaces || *text != ' ')
      width += font->width[UCHAR (*text)];
    else
      ++ns;
  }
  if (nspaces)
    *nspaces = ns;
  return width;
}
