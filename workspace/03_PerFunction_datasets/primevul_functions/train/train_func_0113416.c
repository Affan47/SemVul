
    CImg<Tfloat> get_normalize() const {
      return CImg<Tfloat>(*this,false).normalize();
}
