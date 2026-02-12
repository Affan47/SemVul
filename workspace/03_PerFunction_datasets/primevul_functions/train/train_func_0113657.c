
    CImg<Tuchar> get_YUVtoRGB() const {
      return CImg< Tuchar>(*this,false).YUVtoRGB();
}
