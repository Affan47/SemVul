
    CImg<Tfloat> get_log() const {
      return CImg<Tfloat>(*this,false).log();
}
