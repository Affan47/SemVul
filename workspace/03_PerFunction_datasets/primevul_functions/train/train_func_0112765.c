
    CImg<T> get_erode(const unsigned int sx, const unsigned int sy, const unsigned int sz=1) const {
      return (+*this).erode(sx,sy,sz);
}
