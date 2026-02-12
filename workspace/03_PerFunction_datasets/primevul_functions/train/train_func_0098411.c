static int ntop_rrd_fetch(lua_State* vm) {
  unsigned long i, j, step = 0, ds_cnt = 0;
  rrd_value_t *data, *p;
  char **names;
  char *filename, *cf;
  time_t t, start, end;
  int status;

  if ((status = __ntop_rrd_args(vm, &filename, &cf, &start, &end)) != CONST_LUA_OK) return status;

  ntop->getTrace()->traceEvent(TRACE_INFO, "%s(%s)", __FUNCTION__, filename);

  reset_rrd_state();

  if ((status = __ntop_rrd_status(vm, rrd_fetch_r(filename, cf, &start, &end, &step, &ds_cnt, &names, &data), filename, cf)) != CONST_LUA_OK) return status;

  lua_pushnumber(vm, (lua_Number) start);
  lua_pushnumber(vm, (lua_Number) step);


  lua_newtable(vm);
  for(i=0; i<ds_cnt; i++) {
    lua_pushstring(vm, names[i]);
    lua_rawseti(vm, -2, i+1);
    rrd_freemem(names[i]);
  }
  rrd_freemem(names);


  lua_newtable(vm);
  p = data;
  for(t=start+1, i=0; t<end; t+=step, i++) {
    lua_newtable(vm);
    for(j=0; j<ds_cnt; j++) {
      rrd_value_t value = *p++;

      if(value != DNAN ) {
        lua_pushnumber(vm, (lua_Number)value);
        lua_rawseti(vm, -2, j+1);

      }
    }
    lua_rawseti(vm, -2, i+1);
  }
  rrd_freemem(data);


  lua_pushnumber(vm, (lua_Number) end);


  return(5);
}
