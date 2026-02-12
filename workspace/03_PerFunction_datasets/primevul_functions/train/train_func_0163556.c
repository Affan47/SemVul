return *ptr_max;
    }


    const T& max() const {
      if (is_empty())
        throw CImgInstanceException(_cimglist_instance
                                    "max(): Empty instance.",
                                    cimglist_instance);
      const T *ptr_max = _data->_data;
      T max_value = *ptr_max;
      cimglist_for(*this,l) {
        const CImg<T>& img = _data[l];
}
