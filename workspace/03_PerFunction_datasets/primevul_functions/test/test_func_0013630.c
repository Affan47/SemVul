int luaV_tointeger (const TValue *obj, lua_Integer *p, F2Imod mode) {
  TValue v;
  if (l_strton(obj, &v))
    obj = &v;
  return luaV_tointegerns(obj, p, mode);
}
