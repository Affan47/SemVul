
    CImg<Tfloat> get_RGBtoHSL() const {
      return CImg<Tfloat>(*this,false).RGBtoHSL();
}
