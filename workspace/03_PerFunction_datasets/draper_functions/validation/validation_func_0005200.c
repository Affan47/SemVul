clampRoundConvert(Nrrd *nout, const Nrrd *nin, int type,
                  int doClamp, int roundDir) {
  static const char me[]="clampRoundConvert";
  char typeS[AIR_STRLEN_SMALL];
  size_t num, size[NRRD_DIM_MAX];

  if (!( nin && nout
         && !nrrdCheck(nin)
         && !airEnumValCheck(nrrdType, type) )) {
    biffAddf(NRRD, "%s: invalid args", me);
    return 1;
  }
  if (nin->type == nrrdTypeBlock || type == nrrdTypeBlock) {
    biffAddf(NRRD, "%s: can't convert to or from nrrd type %s", me,
             airEnumStr(nrrdType, nrrdTypeBlock));
    return 1;
  }
  if (nout == nin && nrrdTypeSize[type] != nrrdTypeSize[nin->type]) {
    biffAddf(NRRD, "%s: nout==nin but input,output type sizes unequal", me);
    return 1;
  }
  if (nrrdStateDisallowIntegerNonExist
      && !nrrdTypeIsIntegral[nin->type] && nrrdTypeIsIntegral[type]) {


    if (nrrdHasNonExist(nin)) {
      biffAddf(NRRD, "%s: can't convert to integral values (%s) with "
               "non-existent values in input", me,
               airEnumStr(nrrdType, type));
      return 1;
    }
  }


  if (type == nin->type) {
    if (nout == nin) {


    } else {
      if (nrrdCopy(nout, nin)) {
        biffAddf(NRRD, "%s: couldn't copy input to output", me);
        return 1;
      }
    }
  } else {

    nrrdAxisInfoGet_nva(nin, nrrdAxisInfoSize, size);


    if (nrrdMaybeAlloc_nva(nout, type, nin->dim, size)) {
      biffAddf(NRRD, "%s: failed to allocate output", me);
      return 1;
    }


    num = nrrdElementNumber(nin);
    if (roundDir) {
      _nrrdCastClampRound[nout->type][nin->type](nout->data, nin->data, num,
                                                 doClamp, roundDir);
    } else if (doClamp) {
      _nrrdClampConv[nout->type][nin->type](nout->data, nin->data, num);
    } else {
      _nrrdConv[nout->type][nin->type](nout->data, nin->data, num);
    }
    nout->blockSize = 0;


    nrrdAxisInfoCopy(nout, nin, NULL, NRRD_AXIS_INFO_NONE);
    sprintf(typeS, "(%s)", airEnumStr(nrrdType, nout->type));
    if (nrrdContentSet_va(nout, typeS, nin, "")) {
      biffAddf(NRRD, "%s:", me);
      return 1;
    }


    if (nrrdBasicInfoCopy(nout, nin,
                          NRRD_BASIC_INFO_DATA_BIT
                          | NRRD_BASIC_INFO_TYPE_BIT
                          | NRRD_BASIC_INFO_BLOCKSIZE_BIT
                          | NRRD_BASIC_INFO_DIMENSION_BIT
                          | NRRD_BASIC_INFO_CONTENT_BIT
                          | NRRD_BASIC_INFO_COMMENTS_BIT
                          | (nrrdStateKeyValuePairsPropagate
                             ? 0
                             : NRRD_BASIC_INFO_KEYVALUEPAIRS_BIT))) {
      biffAddf(NRRD, "%s:", me);
      return 1;
    }
  }
  return 0;
}
