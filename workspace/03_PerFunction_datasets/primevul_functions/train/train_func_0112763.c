
    CImg<Tfloat> get_min(const char *const expression) const {
      return CImg<Tfloat>(*this,false).min(expression);
}
