
    CImg<Tfloat> get_sinc() const {
      return CImg<Tfloat>(*this,false).sinc();
}
