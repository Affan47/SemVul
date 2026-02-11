make_ldif(int type, char *name, char *value, ber_len_t vallen)
{
  char *ldif;

  if ((ldif = ldif_put(type, name, value, vallen)) == NULL)
	return(NULL);

  return(ldif);
}
