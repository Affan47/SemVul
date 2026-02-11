check_all_modules(OPT *aod)
{
  int i, found;
  const lam_ssi_t *ls;


  for (found = i = 0; lam_ssi_rpi_modules[i] != NULL; ++i) {
    ls = lam_ssi_rpi_modules[i];
    if (lam_ssi_rpi_verbose > 0)
      lam_debug(lam_ssi_rpi_did, "open: opening rpi module %s",
                ls->ssi_module_name);
    if (ls->ssi_open_module == NULL ||
	(ls->ssi_open_module != NULL &&
	 ls->ssi_open_module(aod) == 1)) {


      if (lam_ssi_rpi_verbose > 10)
        lam_debug(lam_ssi_rpi_did, "open: opened rpi module %s",
                  ls->ssi_module_name);
      al_insert(lam_ssi_rpi_base_opened, &lam_ssi_rpi_modules[i]);
      found = 1;


      if (lam_ssi_base_param_find("rpi", (char*) ls->ssi_module_name,
                                  "priority") == LAMERROR)
        lam_ssi_base_param_register_int("rpi", (char*) ls->ssi_module_name,
                                        "priority", NULL, 0);
    } else {
      if (lam_ssi_rpi_verbose > 10)
        lam_debug(lam_ssi_rpi_did, "open: rpi module %s did not open",
                  ls->ssi_module_name);
      lam_ssi_base_module_registry_unuse((lam_ssi_t*) ls);
    }
  }


  if (found == 0) {
    if (lam_ssi_rpi_verbose > 10)
      lam_debug(lam_ssi_rpi_did,
                "open: no rpi moduless available to be opened!");
    show_help("ssi-rpi", "none-available", NULL);
    return LAMERROR;
  }


  return 0;
}
