
    CImg<Tfloat> get_tanh() const {
      return CImg<Tfloat>(*this,false).tanh();
}
