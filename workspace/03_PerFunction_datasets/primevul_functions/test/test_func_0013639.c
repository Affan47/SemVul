l_sinline int LEfloatint (lua_Number f, lua_Integer i) {
  if (l_intfitsf(i))
    return luai_numle(f, cast_num(i));
  else {
    lua_Integer fi;
    if (luaV_flttointeger(f, &fi, F2Iceil))
      return fi <= i;
    else
      return f < 0;
  }
}
