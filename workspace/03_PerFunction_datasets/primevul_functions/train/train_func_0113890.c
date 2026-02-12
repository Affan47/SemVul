
    CImg<Tuchar> get_RGBtoCMY() const {
      return CImg<Tfloat>(*this,false).RGBtoCMY();
}
