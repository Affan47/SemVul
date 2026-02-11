bitWidth(uint32 x) {
    int r = 0;
    Assert(x <= 0xffffffff);
    if (x & 0xffff0000) { r += 16; x >>= 16; }
    if (x & 0xff00) { r += 8; x >>= 8; }
    if (x & 0xf0) { r += 4; x >>= 4; }
    if (x & 0xc) { r += 2; x >>= 2; }
    if (x & 2) { r += 1; x >>=1; }
    if (x & 1) r += 1;
    return r;
  }
