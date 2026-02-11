InputString(szPrompt, sz)
byte *szPrompt, *sz;
{
  FILE *file;
  int cch;

  file = is.S; is.S = stdout;
  PrintSz(szPrompt);
  AnsiColor(kYellow);
  PrintSz(" > ");
  AnsiColor(kDefault);
  if (fgets(sz, cchSzMax, stdin) == NULL)
    Terminate(tcForce);
  cch = CchSz(sz);
  while (cch > 0 && sz[cch-1] < ' ')
    cch--;
  sz[cch] = chNull;
  is.S = file;
  is.cchCol = 0;
}
