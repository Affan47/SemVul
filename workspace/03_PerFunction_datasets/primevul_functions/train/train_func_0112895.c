
    CImg<T>& discard(const char axis=0) {
      return get_discard(axis).move_to(*this);
}
