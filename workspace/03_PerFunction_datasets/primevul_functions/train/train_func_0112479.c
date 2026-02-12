
    CImg<Tuchar> get_HSLtoRGB() const {
      return CImg<Tuchar>(*this,false).HSLtoRGB();
}
