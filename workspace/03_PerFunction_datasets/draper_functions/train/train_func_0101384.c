gxqdrgb (gaint clr, gaint *r, gaint *g, gaint *b) {
  if (clr>=0 && clr<16) {
    *r = reds[clr];
    *g = greens[clr];
    *b = blues[clr];
  }
  return;
}
