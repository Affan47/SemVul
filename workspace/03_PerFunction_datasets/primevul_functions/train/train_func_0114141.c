
    CImg<Tfloat> get_HSItoRGB() const {
      return CImg< Tuchar>(*this,false).HSItoRGB();
}
