list_PointList_fillin(int sel, Geom *geom, va_list *args) {
  TransformPtr t;
  int n_points1;
  HPoint3 *plist;
  List *l = (List *)geom;

  t = va_arg(*args, TransformPtr);
  (void)va_arg(*args, int);
  plist = va_arg(*args, HPoint3 *);

  n_points1 = (int)(long)GeomCall(GeomMethodSel("PointList_length"), l->car);

  GeomCall(GeomMethodSel("PointList_fillin"), l->car, t, 0, plist);
  GeomCall(GeomMethodSel("PointList_fillin"), (Geom *)l->cdr, t, 0,
	   &plist[n_points1]);
  return plist;
}
