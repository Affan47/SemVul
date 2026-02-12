
    CImg<Tfloat> get_log10() const {
      return CImg<Tfloat>(*this,false).log10();
}
