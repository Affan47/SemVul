
    CImg<T> get_dilate(const unsigned int sx, const unsigned int sy, const unsigned int sz=1) const {
      return (+*this).dilate(sx,sy,sz);
}
