l_sinline int LEnum (const TValue *l, const TValue *r) {
  lua_assert(ttisnumber(l) && ttisnumber(r));
  if (ttisinteger(l)) {
    lua_Integer li = ivalue(l);
    if (ttisinteger(r))
      return li <= ivalue(r);
    else
      return LEintfloat(li, fltvalue(r));
  }
  else {
    lua_Number lf = fltvalue(l);
    if (ttisfloat(r))
      return luai_numle(lf, fltvalue(r));
    else
      return LEfloatint(lf, ivalue(r));
  }
}
