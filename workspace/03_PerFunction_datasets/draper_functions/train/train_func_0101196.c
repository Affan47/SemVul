reconnect(void) {
    delete client; client = NULL;
    logger.msg(DEBUG, "Re-creating an A-REX client");
    client = new ClientSOAP(cfg, rurl, timeout);


    if(arex_enabled) {
      set_arex_namespaces(arex_ns);
    } else {
      set_bes_namespaces(arex_ns);
    }
    return true;
  }
