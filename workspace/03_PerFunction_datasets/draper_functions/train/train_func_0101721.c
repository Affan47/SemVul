luaH_pos (Hash *t, TObject *r) {
  Node *n = luaH_present(t, r);
  luaL_arg_check(ttype(val(n)) != LUA_T_NIL, 2, "key not found");
  return n-(t->node);
}
