mrglst(ParamElem a[], ParamElem b[])
#else
void mrglst(a, b)
     ParamElem a[], b[];
#endif
{
  int i,last;

  for (last = 0; a[last].code != EOF; last++);
  for (i = 0; b[i].code != EOF; i++)
    if (!inlst(a, b[i].code)) {
      a[last++] = b[i];
      a[last].code = EOF;
    }
}
