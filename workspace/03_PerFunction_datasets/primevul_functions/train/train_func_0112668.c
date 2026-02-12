
    CImg<T> get_transpose() const {
      return get_permute_axes("yxzc");
}
