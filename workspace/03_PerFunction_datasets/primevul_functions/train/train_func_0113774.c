
    CImg<Tlong> get_cumulate(const char *const axes) const {
      return CImg<Tlong>(*this,false).cumulate(axes);
}
