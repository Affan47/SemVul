cbase(int c)
{ static char base[6] = "acgt..";
  if (c < Adenine) return('#');
  if (c > NOBASE) return((char)c);
  return(base[c]); }
