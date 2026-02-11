getnarg (Hash *a) {
  TObject index;
  TObject *value;

  ttype(&index) = LUA_T_STRING;
  tsvalue(&index) = luaS_new("n");
  value = luaH_get(a, &index);
  return (ttype(value) == LUA_T_NUMBER) ? nvalue(value) : getsize(a);
}
