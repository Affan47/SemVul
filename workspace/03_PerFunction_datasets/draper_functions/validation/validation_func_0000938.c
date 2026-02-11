soap_env_get_fault(SoapEnv * env)
{
  xmlNodePtr node;

  node = soap_env_get_body(env);

  if (!node)
    return NULL;

  while (node != NULL)
  {
    if (!xmlStrcmp(node->name, BAD_CAST "Fault"))
      return node;
    node = soap_xml_get_next(node);
  }


  return NULL;
}
