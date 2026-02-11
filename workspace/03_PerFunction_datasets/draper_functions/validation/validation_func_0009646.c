vardef_position (varname) char *varname; {
  register int k = 0;

  if(varname == NIL)
    return -1;

  while ((k < MAXVARDEFS) && variantDefs[k].name) {
    if (!strcmp(variantDefs[k].name, varname))
      return k;
    k++;
  }
  return -1;
}
