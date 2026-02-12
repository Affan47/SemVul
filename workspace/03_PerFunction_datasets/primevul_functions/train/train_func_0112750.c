
    CImg<Tuchar> get_RGBtoYCbCr() const {
      return CImg<Tuchar>(*this,false).RGBtoYCbCr();
}
