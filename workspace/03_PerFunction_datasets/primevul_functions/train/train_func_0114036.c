
    CImg<T> get_mirror(const char *const axes) const {
      return (+*this).mirror(axes);
}
