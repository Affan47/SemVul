log_cline(FILE *lf)
{
  int i = 78;

  fputc('#', lf);
  while(i--) fputc('-', lf);
  fputc('\n', lf);
}
