
    CImg<T>& fill(const T& val0, const T& val1, const T& val2, const T& val3, const T& val4) {
      if (is_empty()) return *this;
      T *ptrd, *ptre = end() - 4;
      for (ptrd = _data; ptrd<ptre; ) {
        *(ptrd++) = val0; *(ptrd++) = val1; *(ptrd++) = val2; *(ptrd++) = val3; *(ptrd++) = val4;
      }
      ptre+=4;
      switch (ptre - ptrd) {
      case 4 : *(--ptre) = val3;
      case 3 : *(--ptre) = val2;
      case 2 : *(--ptre) = val1;
      case 1 : *(--ptre) = val0;
      }
      return *this;
}
