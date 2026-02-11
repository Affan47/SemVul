dyeColorInit(dyeColor *col) {

  if (col) {
    ELL_3V_SET(col->val[0], AIR_NAN, AIR_NAN, AIR_NAN);
    ELL_3V_SET(col->val[1], AIR_NAN, AIR_NAN, AIR_NAN);
    col->xWhite = col->yWhite = AIR_NAN;
    col->spc[0] = dyeSpaceUnknown;
    col->spc[1] = dyeSpaceUnknown;
    col->ii = 0;
  }
  return col;
}
