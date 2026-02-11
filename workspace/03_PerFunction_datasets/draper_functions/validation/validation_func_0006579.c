eat_line(GtSequenceBuffer *sb,
                           unsigned long *currentfileread)
{
  int currentchar;
  do {
    currentchar = inlinebuf_getchar(sb, sb->pvt->inputstream);
    if (currentchar == EOF)
      return EOF;
    (*currentfileread)++;
  } while (currentchar != NEWLINESYMBOL);
  inlinebuf_ungetchar(sb);
  (*currentfileread)--;
  return 0;
}
