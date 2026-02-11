nrrdByteSkip(FILE *dataFile, Nrrd *nrrd, NrrdIoState *nio) {
  static const char me[]="nrrdByteSkip";

  if (!( dataFile && nrrd && nio )) {
    biffAddf(NRRD, "%s: got NULL pointer", me);
    return 1;
  }


  if (_nrrdByteSkipSkip(dataFile, nrrd, nio, nio->byteSkip)) {
    biffAddf(NRRD, "%s: trouble", me);
    return 1;
  }

  return 0;
}
