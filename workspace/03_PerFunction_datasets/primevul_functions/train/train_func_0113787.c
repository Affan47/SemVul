
    CImg<Tfloat> get_max(const char *const expression) const {
      return CImg<Tfloat>(*this,false).max(expression);
}
