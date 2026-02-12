static int prop_lookup(unsigned long code, unsigned long n) {
  long l, r, m;


  if ((l = _ucprop_offsets[n]) == 0xffff)
    return 0;


  for (m = 1; n + m < _ucprop_size && _ucprop_offsets[n + m] == 0xffff; m++)
    ;

  r = _ucprop_offsets[n + m] - 1;

  while (l <= r) {


    m = (l + r) >> 1;
    m -= (m & 1);
    if (code > _ucprop_ranges[m + 1])
      l = m + 2;
    else if (code < _ucprop_ranges[m])
      r = m - 2;
    else if (code >= _ucprop_ranges[m] && code <= _ucprop_ranges[m + 1])
      return 1;
  }
  return 0;

}
