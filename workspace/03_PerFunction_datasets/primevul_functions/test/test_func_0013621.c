l_sinline int LEintfloat (lua_Integer i, lua_Number f) {
  if (l_intfitsf(i))
    return luai_numle(cast_num(i), f);
  else {
    lua_Integer fi;
    if (luaV_flttointeger(f, &fi, F2Ifloor))
      return i <= fi;
    else
      return f > 0;
  }
}
