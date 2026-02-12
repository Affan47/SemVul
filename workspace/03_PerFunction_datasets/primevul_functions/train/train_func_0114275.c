
    CImg<Tuchar> get_CMYKtoRGB() const {
      return CImg<Tuchar>(*this,false).CMYKtoRGB();
}
