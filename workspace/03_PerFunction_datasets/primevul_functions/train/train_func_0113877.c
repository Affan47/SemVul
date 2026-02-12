
    CImg<Tfloat> get_RGBtoHSV() const {
      return CImg<Tfloat>(*this,false).RGBtoHSV();
}
