sort_two(int v0, int v1, int *r0, int *r1) {
  if (v0 <= v1) {
     if (r0) *r0 = v0;
     if (r1) *r1 = v1;
  }
  else {
     if (r0) *r0 = v1;
     if (r1) *r1 = v0;
  }
}
