
    CImg<Tfloat> get_RGBtoHSI() const {
      return CImg<Tfloat>(*this,false).RGBtoHSI();
}
