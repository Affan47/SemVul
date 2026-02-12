cgi_compare_variables(
    const _cgi_var_t *v1,
    const _cgi_var_t *v2)
{
  return (_cups_strcasecmp(v1->name, v2->name));
}
