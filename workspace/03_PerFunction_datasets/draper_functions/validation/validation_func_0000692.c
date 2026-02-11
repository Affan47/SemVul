find_lattice_value_parts (tree real, tree imag)
{
  int r, i;
  complex_lattice_t ret;

  r = some_nonzerop (real);
  i = some_nonzerop (imag);
  ret = r * ONLY_REAL + i * ONLY_IMAG;


  if (ret == UNINITIALIZED)
    ret = ONLY_REAL;

  return ret;
}
