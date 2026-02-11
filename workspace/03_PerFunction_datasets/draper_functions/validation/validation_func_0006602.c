inst_PointList_fillin(int sel, Geom *geom, va_list *args) {
  Inst *inst = (Inst *)geom;
  HPoint3 *plist;
  int coordsys;
  GeomIter *it;
  Transform Tnew;
  int i, n_points;
  TransformPtr t;

  t = va_arg(*args, TransformPtr);
  coordsys = va_arg(*args, int);
  plist = va_arg(*args, HPoint3 *);

  n_points = (int)(long)GeomCall(GeomMethodSel("PointList_length"), inst->geom);

  it = GeomIterate(geom, DEEP);
  for (i = 0; NextTransform(it, Tnew); i += n_points)
    if (coordsys == POINTLIST_SELF) {
      TmConcat(Tnew, t, Tnew);
      GeomCall(GeomMethodSel("PointList_fillin"), inst->geom, &Tnew[0][0],
	       coordsys, &plist[i]);
    } else if (coordsys == POINTLIST_PRIMITIVE)
      GeomCall(GeomMethodSel("PointList_fillin"), inst->geom, t, coordsys,
	       &plist[i]);
    else {
      OOGLError(1, "Unrecognized coordinate system in inst_PointList_fillin");
      return NULL;
    }

  return plist;

}
