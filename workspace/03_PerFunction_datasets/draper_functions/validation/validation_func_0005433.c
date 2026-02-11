Zero() {
  for (int i = 0; i < used_digits_; ++i) {
    bigits_[i] = 0;
  }
  used_digits_ = 0;
  exponent_ = 0;
}
