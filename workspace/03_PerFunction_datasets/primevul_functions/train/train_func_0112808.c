
    CImg<T> get_fill(const T& val) const {
      return CImg<T>(_width,_height,_depth,_spectrum).fill(val);
}
