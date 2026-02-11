newkey(char* name, int sharps, char accidental[], int mult[])

{
  struct key* k;
  int i;

  k = (struct key*)checkmalloc(sizeof(struct key));
  k->name = addstring(name);
  k->sharps = sharps;
  for (i=0; i<7; i++) {
    k->map[i] = accidental[i];
    k->mult[i] = mult[i];
  };
  return(k);
}
