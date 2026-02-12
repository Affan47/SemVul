
    CImg<Tfloat> get_abs() const {
      return CImg<Tfloat>(*this,false).abs();
}
