gageShapeCopy(const gageShape *shp) {
  gageShape *nhp;

  if ((nhp = gageShapeNew())) {

    memcpy(nhp, shp, sizeof(gageShape));
  }
  return nhp;
}
