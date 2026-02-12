
    CImg<Tfloat> get_XYZtoxyY() const {
      return CImg<Tfloat>(*this,false).XYZtoxyY();
}
