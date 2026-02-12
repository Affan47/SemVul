
    CImg<Tfloat> get_sign() const {
      return CImg<Tfloat>(*this,false).sign();
}
