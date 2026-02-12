lua_Integer luaV_shiftl (lua_Integer x, lua_Integer y) {
  if (y < 0) {
    if (y <= -NBITS) return 0;
    else return intop(>>, x, -y);
  }
  else {
    if (y >= NBITS) return 0;
    else return intop(<<, x, y);
  }
}
