add(unsigned long groveIndex, unsigned long n)
{
  if (groveIndex >= v_.size())
    v_.resize(groveIndex + 1);
  Vector<char> &elems = v_[groveIndex];
  if (n >= elems.size()) {
    for (size_t k = 1 + (n - elems.size()); k > 0; --k)
      elems.push_back(0);
  }
  elems[n] = 1;
}
