void Lua::setInterface(const char *user) {
  char key[64], ifname[MAX_INTERFACE_NAME_LEN];
  bool enforce_allowed_interface = false;

  if(user[0] != '\0') {


    if(snprintf(key, sizeof(key), CONST_STR_USER_ALLOWED_IFNAME, user)
       && !ntop->getRedis()->get(key, ifname, sizeof(ifname))) {

      enforce_allowed_interface = true;
      goto set_preferred_interface;
    } else if(snprintf(key, sizeof(key), "ntopng.prefs.%s.ifname", user)
	      && ntop->getRedis()->get(key, ifname, sizeof(ifname)) < 0) {

    set_default_if_name_in_session:
      snprintf(ifname, sizeof(ifname), "%s",
	       ntop->getInterfaceAtId(NULL ,
				      0)->get_name());
      lua_push_str_table_entry(L, "ifname", ifname);
      ntop->getRedis()->set(key, ifname, 3600 );
    } else {
      goto set_preferred_interface;
    }
  } else {

    snprintf(key, sizeof(key), "ntopng.prefs.ifname");
    if(ntop->getRedis()->get(key, ifname, sizeof(ifname)) < 0) {
      goto set_preferred_interface;
    }

  set_preferred_interface:
    NetworkInterface *iface;

    if((iface = ntop->getNetworkInterface(NULL ,
					      ifname)) != NULL) {

      lua_push_str_table_entry(L, "ifname", iface->get_name());
    } else if(!enforce_allowed_interface) {
      goto set_default_if_name_in_session;
    } else {


    }
  }
}
