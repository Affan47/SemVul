TextWidthFont (BFont_Info * Font, char *text)
{
  int i = 0, x = 0;

  while (text[i] != '\0')
    {
      x += CharWidth (Font, text[i]);
      i++;
    }
  return x;
}
