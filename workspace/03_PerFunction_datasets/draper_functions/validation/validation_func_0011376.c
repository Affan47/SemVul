Read_Overlap(FILE *input, Overlap *ovl)
{ if (fread( ((char *) ovl) + PtrSize, OvlIOSize, 1, input) != 1)
    return (1);
  return (0);
}
