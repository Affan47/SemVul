static int ntop_get_default_interface_name(lua_State* vm) {
  char ifname[MAX_INTERFACE_NAME_LEN];
  ntop->getTrace()->traceEvent(TRACE_DEBUG, "%s() called", __FUNCTION__);

  if(ntop->getInterfaceAllowed(vm, ifname)) {


    lua_pushstring(vm,
		   ntop->getNetworkInterface(ifname)->get_name());
  } else {
    lua_pushstring(vm, ntop->getInterfaceAtId(NULL,
					      0)->get_name());
  }
  return(CONST_LUA_OK);
}
