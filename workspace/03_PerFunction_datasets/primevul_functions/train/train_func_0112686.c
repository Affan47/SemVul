
    CImg<T>& laplacian() {
      return get_laplacian().move_to(*this);
}
