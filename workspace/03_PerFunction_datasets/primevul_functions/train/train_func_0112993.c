
    CImg<Tuchar> get_YCbCrtoRGB() const {
      return CImg<Tuchar>(*this,false).YCbCrtoRGB();
}
