void Lua::lua_register_classes(lua_State *L, bool http_mode) {
  static const luaL_Reg _meta[] = { { NULL, NULL } };
  int i;

  ntop_class_reg ntop_lua_reg[] = {
    { "interface", ntop_interface_reg },
    { "ntop",      ntop_reg },
    {NULL,         NULL}
  };

  if(!L) return;

  luaopen_lsqlite3(L);

  for(i=0; ntop_lua_reg[i].class_name != NULL; i++) {
    int lib_id, meta_id;


    lua_createtable(L, 0, 0);
    lib_id = lua_gettop(L);


    luaL_newmetatable(L, ntop_lua_reg[i].class_name);
    meta_id = lua_gettop(L);
    luaL_register(L, NULL, _meta);


    lua_newtable(L), luaL_register(L, NULL, ntop_lua_reg[i].class_methods);
    lua_setfield(L, meta_id, "__index");


    lua_setmetatable(L, lib_id);


    lua_setglobal(L, ntop_lua_reg[i].class_name);
  }

  if(http_mode) {

    lua_register(L, "print", ntop_lua_http_print);
  } else
    lua_register(L, "print", ntop_lua_cli_print);

#ifdef NTOPNG_PRO
  if(ntop->getPro()->has_valid_license()) {
    lua_register(L, "ntopRequire", ntop_lua_require);
    luaL_dostring(L, "table.insert(package.loaders, 1, ntopRequire)");
    lua_register(L, "dofile", ntop_lua_dofile);
  }
#endif
}
