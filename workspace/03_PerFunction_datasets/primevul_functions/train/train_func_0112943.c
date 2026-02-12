
    CImg<T> get_autocrop(const T *const color=0, const char *const axes="zyx") const {
      return (+*this).autocrop(color,axes);
}
