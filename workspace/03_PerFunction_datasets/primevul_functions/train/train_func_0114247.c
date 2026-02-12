
    T at(const int offset, const T& out_value) const {
      return (offset<0 || offset>=(int)size())?out_value:(*this)[offset];
}
