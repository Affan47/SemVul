isZero() const {
  for (int i=0; i<dim; i++)
    if (_rep[i] != 0) return false;
  return true;
}
