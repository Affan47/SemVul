
    inline cimg_ulong& rng() {
      static cimg_ulong rng = 0xB16B00B5U;
      return rng;
}
