
    CImg<Tfloat> get_sRGBtoRGB() const {
      return CImg<Tfloat>(*this,false).sRGBtoRGB();
}
