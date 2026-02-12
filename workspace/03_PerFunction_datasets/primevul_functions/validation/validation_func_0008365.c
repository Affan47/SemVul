int do_nothing(int8_t filter, char cmode) {
  if (cmode == 'c') {
    return (filter == BLOSC_NOFILTER);
  } else {

    return ((filter == BLOSC_NOFILTER) || (filter == BLOSC_TRUNC_PREC));
  }
}
