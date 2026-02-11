checkForModifier(Tcl_Obj * CONST objv[], int numberModifiers, char *modifier) {
  int i;
  if (numberModifiers == 0) return 0;
  for (i = 2; i-2 < numberModifiers; i++) {
    char *ov = ObjStr(objv[i]);

    if (ov[1] == modifier[1] && !strcmp(ov, modifier))
      return 1;
  }
  return 0;
}
