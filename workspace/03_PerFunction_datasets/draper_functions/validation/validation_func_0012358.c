hesiod_to_bind(void *context, const char *name, const char *type)
{
  struct hesiod_p *ctx = (struct hesiod_p *) context;
  char bindname[MAXDNAME], *p, *ret, *idn_ret, **rhs_list = NULL;
  const char *rhs;
  int len, rc;

  if (strlen(name) > sizeof(bindname) - 1)
    {
      errno = EMSGSIZE;
      return NULL;
    }
  strcpy(bindname, name);


  p = strchr(bindname, '@');
  if (p)
    {
      *p++ = 0;
      if (strchr(p, '.'))
	rhs = name + (p - bindname);
      else
	{
	  rhs_list = hesiod_resolve(context, p, "rhs-extension");
	  if (rhs_list)
	    rhs = *rhs_list;
	  else
	    {
	      errno = ENOENT;
	      return NULL;
	    }
	}
    } else
      rhs = ctx->rhs;


  len = strlen(bindname) + 1 + strlen(type);
  if (ctx->lhs)
    len += strlen(ctx->lhs) + ((ctx->lhs[0] != '.') ? 1 : 0);
  len += strlen(rhs) + ((rhs[0] != '.') ? 1 : 0);
  if (len > sizeof(bindname) - 1)
    {
      if (rhs_list)
	hesiod_free_list(context, rhs_list);
      errno = EMSGSIZE;
      return NULL;
    }


  strcat(bindname, ".");
  strcat(bindname, type);
  if (ctx->lhs)
    {
      if (ctx->lhs[0] != '.')
	strcat(bindname, ".");
      strcat(bindname, ctx->lhs);
    }
  if (rhs[0] != '.')
    strcat(bindname, ".");
  strcat(bindname, rhs);


  if (rhs_list)
    hesiod_free_list(context, rhs_list);


#ifdef HAVE_LIBIDN
  rc = idna_to_ascii_lz(bindname, &idn_ret, 0);
  if (rc != IDNA_SUCCESS)
    {
      errno = EINVAL;
      return NULL;
    }
  ret = strdup(idn_ret);
  idn_free(idn_ret);
#else
  ret = strdup(bindname);
#endif
  if (!ret)
    {
      errno = ENOMEM;
      return NULL;
    }
  return ret;
}
