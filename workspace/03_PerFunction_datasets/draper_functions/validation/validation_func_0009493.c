nrrdSpaceDimensionSet(Nrrd *nrrd, unsigned int spaceDim) {
  static const char me[]="nrrdSpaceDimensionSet";

  if (!nrrd) {
    biffAddf(NRRD, "%s: got NULL pointer", me);
    return 1;
  }
  if (!( spaceDim <= NRRD_SPACE_DIM_MAX )) {
    biffAddf(NRRD, "%s: given spaceDim (%u) not valid", me, spaceDim);
    return 1;
  }
  nrrd->space = nrrdSpaceUnknown;
  nrrd->spaceDim = spaceDim;
  return 0;
}
