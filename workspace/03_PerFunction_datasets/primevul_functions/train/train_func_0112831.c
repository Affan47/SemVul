
    CImg<Tuchar> get_HSVtoRGB() const {
      return CImg<Tuchar>(*this,false).HSVtoRGB();
}
