
    CImg<Tuchar> get_XYZtoRGB(const bool use_D65=true) const {
      return CImg<Tuchar>(*this,false).XYZtoRGB(use_D65);
}
