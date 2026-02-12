cgiGetSize(const char *name)
{
  _cgi_var_t	*var;


  if ((var = cgi_find_variable(name)) == NULL)
    return (0);

  return (var->nvalues);
}
