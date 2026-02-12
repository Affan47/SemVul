php_next_marker(const req::ptr<File>& file, int , int ff_read) {
  int a=0, marker;


  if (!ff_read) {
    size_t extraneous = 0;

    while ((marker = file->getc()) != 0xff) {
      if (marker == EOF) {
        return M_EOI;
      }
      extraneous++;
    }
    if (extraneous) {
      raise_warning("corrupt JPEG data: %zu extraneous bytes before marker",
                    extraneous);
    }
  }
  a = 1;
  do {
    if ((marker = file->getc()) == EOF)
    {
      return M_EOI;
    }
    ++a;
  } while (marker == 0xff);
  if (a < 2)
  {
    return M_EOI;
  }
  return (unsigned int)marker;
}
