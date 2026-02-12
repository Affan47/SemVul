
    CImg<T>& fill(const T& val0, const T& val1, const T& val2, const T& val3, const T& val4, const T& val5,
                  const T& val6, const T& val7, const T& val8, const T& val9) {
      if (is_empty()) return *this;
      T *ptrd, *ptre = end() - 9;
      for (ptrd = _data; ptrd<ptre; ) {
        *(ptrd++) = val0; *(ptrd++) = val1; *(ptrd++) = val2; *(ptrd++) = val3; *(ptrd++) = val4;
        *(ptrd++) = val5; *(ptrd++) = val6; *(ptrd++) = val7; *(ptrd++) = val8; *(ptrd++) = val9;
      }
      ptre+=9;
      switch (ptre - ptrd) {
      case 9 : *(--ptre) = val8;
      case 8 : *(--ptre) = val7;
      case 7 : *(--ptre) = val6;
      case 6 : *(--ptre) = val5;
      case 5 : *(--ptre) = val4;
      case 4 : *(--ptre) = val3;
      case 3 : *(--ptre) = val2;
      case 2 : *(--ptre) = val1;
      case 1 : *(--ptre) = val0;
      }
      return *this;
}
