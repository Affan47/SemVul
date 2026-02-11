acs_is_readonly_namespace(char *ns)
{
  int i;

  if (dacs_disable_readonly_namespaces)
	return(0);

  if (ns == NULL)
#ifdef DEFAULT_NAMESPACE
	ns = DEFAULT_NAMESPACE;
#else
  {
	log_msg((LOG_ERROR_LEVEL,
			 "Invalid variable reference: namespace is required"));
	return(1);
  }
#endif

  for (i = 0; readonly_namespaces[i] != NULL; i++) {
	if (streq(ns, readonly_namespaces[i]))
	  return(1);
  }

  return(0);
}
