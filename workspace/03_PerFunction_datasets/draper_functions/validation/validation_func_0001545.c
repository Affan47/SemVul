nrrdApplyMulti1DRegMap(Nrrd *nout, const Nrrd *nin,
                       const NrrdRange *_range, const Nrrd *nmmap,
                       int typeOut, int rescale) {
  static const char me[]="nrrdApplyMulti1DRegMap";
  NrrdRange *range;
  airArray *mop;

  if (!(nout && nmmap && nin)) {
    biffAddf(NRRD, "%s: got NULL pointer", me);
    return 1;
  }
  mop = airMopNew();
  if (_range) {
    range = nrrdRangeCopy(_range);
    nrrdRangeSafeSet(range, nin, nrrdBlind8BitRangeState);
  } else {
    range = nrrdRangeNewSet(nin, nrrdBlind8BitRangeState);
  }
  airMopAdd(mop, range, (airMopper)nrrdRangeNix, airMopAlways);
  if (_nrrdApply1DSetUp(nout, nin, range, nmmap, kindRmap, typeOut,
                        rescale, AIR_TRUE )
      || _nrrdApply1DLutOrRegMap(nout, nin, range, nmmap, AIR_TRUE ,
                                 rescale, AIR_TRUE )) {
    biffAddf(NRRD, "%s:", me);
    airMopError(mop); return 1;
  }
  airMopOkay(mop);
  return 0;
}
