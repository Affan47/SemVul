bzputc(int c, BZFILE *bzfile)
{
  char cc = (char) c;
  return BZ2_bzwrite(bzfile, &cc, 1) == 1 ? cc : -1;
}
