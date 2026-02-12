return *ptr_min;
    }


    const T& min() const {
      if (is_empty())
        throw CImgInstanceException(_cimglist_instance
                                    "min(): Empty instance.",
                                    cimglist_instance);
      const T *ptr_min = _data->_data;
      T min_value = *ptr_min;
      cimglist_for(*this,l) {
        const CImg<T>& img = _data[l];
}
