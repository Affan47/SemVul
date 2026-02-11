display_clear_display (DISPLAY_LINE **display)
{
  register int i;

  for (i = 0; display[i]; i++)
    {
      display[i]->text[0] = '\0';
      display[i]->textlen = 0;
      display[i]->inverse = 0;
    }
}
