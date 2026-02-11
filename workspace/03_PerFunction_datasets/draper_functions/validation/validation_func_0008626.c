_nrrdMeasureNormalizedL2(void *ans, int ansType,
                         const void *line, int lineType, size_t len,
                         double axmin, double axmax) {
  double val, S, aa, (*lup)(const void*, size_t);
  size_t ii, count;

  L2_BODY(AIR_FALSE);
  if (AIR_EXISTS(S)) {
    aa = sqrt(S)/count;
  } else {
    aa = AIR_NAN;
  }
  nrrdDStore[ansType](ans, aa);
}
