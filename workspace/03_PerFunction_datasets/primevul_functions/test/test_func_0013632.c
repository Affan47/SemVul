l_sinline int LTintfloat (lua_Integer i, lua_Number f) {
  if (l_intfitsf(i))
    return luai_numlt(cast_num(i), f);
  else {
    lua_Integer fi;
    if (luaV_flttointeger(f, &fi, F2Iceil))
      return i < fi;
    else
      return f > 0;
  }
}
