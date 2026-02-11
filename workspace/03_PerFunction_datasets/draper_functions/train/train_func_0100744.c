tenFiberTrace(tenFiberContext *tfx, Nrrd *nfiber, double seed[3]) {
  static const char me[]="tenFiberTrace";

  if (_fiberTraceSet(tfx, NULL, nfiber, NULL, 0, NULL, NULL, seed)) {
    biffAddf(TEN, "%s: problem computing tract", me);
    return 1;
  }

  return 0;
}
