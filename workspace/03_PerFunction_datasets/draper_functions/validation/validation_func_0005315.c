get(void)
{
  if (bufpos < bufend || !eof())
    return buffer[bufpos++];
  return EOF;
}
