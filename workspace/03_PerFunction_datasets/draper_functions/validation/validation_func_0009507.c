vertexWithTriangle(Nrrd *nVertWithTri, limnPolyData *pld) {
  static const char me[]="vertexWithTriangle";
  unsigned int baseVertIdx, primIdx, *vertWithTri, triNum;

  if (!(nVertWithTri && pld)) {
    biffAddf(LIMN, "%s: got NULL pointer", me);
    return 1;
  }
  if ((1 << limnPrimitiveTriangles) != limnPolyDataPrimitiveTypes(pld)) {
    biffAddf(LIMN, "%s: sorry, can only handle %s primitives", me,
             airEnumStr(limnPrimitive, limnPrimitiveTriangles));
    return 1;
  }

  triNum = limnPolyDataPolygonNumber(pld);
  if (nrrdMaybeAlloc_va(nVertWithTri, nrrdTypeUInt, 2,
                        AIR_CAST(size_t, 3),
                        AIR_CAST(size_t, triNum))) {
    biffMovef(LIMN, NRRD, "%s: couldn't allocate output", me);
    return 1;
  }
  vertWithTri = AIR_CAST(unsigned int*, nVertWithTri->data);

  baseVertIdx = 0;
  for (primIdx=0; primIdx<pld->primNum; primIdx++) {
    unsigned int triIdx, *indxLine, totTriIdx, ii;
    triNum = pld->icnt[primIdx]/3;
    for (triIdx=0; triIdx<triNum; triIdx++) {
      totTriIdx = triIdx + baseVertIdx/3;
      indxLine = pld->indx + baseVertIdx + 3*triIdx;
      for (ii=0; ii<3; ii++) {
        (vertWithTri + 3*totTriIdx)[ii] = indxLine[ii];
      }
    }
    baseVertIdx += pld->icnt[primIdx];
  }

  return 0;
}
