static unsigned long case_lookup(unsigned long code, long l, long r,
                                 int field) {
  long m;


  while (l <= r) {


    m = (l + r) >> 1;
    m -= (m % 3);
    if (code > _uccase_map[m])
      l = m + 3;
    else if (code < _uccase_map[m])
      r = m - 3;
    else if (code == _uccase_map[m])
      return _uccase_map[m + field];
  }

  return code;
}
