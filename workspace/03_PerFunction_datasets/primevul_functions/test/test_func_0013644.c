l_sinline int LTfloatint (lua_Number f, lua_Integer i) {
  if (l_intfitsf(i))
    return luai_numlt(f, cast_num(i));
  else {
    lua_Integer fi;
    if (luaV_flttointeger(f, &fi, F2Ifloor))
      return fi < i;
    else
      return f < 0;
  }
}
