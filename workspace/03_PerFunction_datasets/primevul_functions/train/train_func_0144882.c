cgiGetArray(const char *name,
            int        element)
{
  _cgi_var_t	*var;


  if ((var = cgi_find_variable(name)) == NULL)
    return (NULL);

  if (element < 0 || element >= var->nvalues)
    return (NULL);

  return (_cupsStrRetain(var->values[element]));
}
