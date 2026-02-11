ss_median5(const unsigned char *Td, const int *PA,
           int *v1, int *v2, int *v3, int *v4, int *v5) {
  int *t;
  if(Td[PA[*v2]] > Td[PA[*v3]]) { SWAP(v2, v3); }
  if(Td[PA[*v4]] > Td[PA[*v5]]) { SWAP(v4, v5); }
  if(Td[PA[*v2]] > Td[PA[*v4]]) { SWAP(v2, v4); SWAP(v3, v5); }
  if(Td[PA[*v1]] > Td[PA[*v3]]) { SWAP(v1, v3); }
  if(Td[PA[*v1]] > Td[PA[*v4]]) { SWAP(v1, v4); SWAP(v3, v5); }
  if(Td[PA[*v3]] > Td[PA[*v4]]) { return v4; }
  return v3;
}
