acl_read(uschar *(*func)(void), uschar **error)
{
acl_block *yield = NULL;
acl_block **lastp = &yield;
acl_block *this = NULL;
acl_condition_block *cond;
acl_condition_block **condp = NULL;
uschar *s;

*error = NULL;

while ((s = (*func)()) != NULL)
  {
  int v, c;
  BOOL negated = FALSE;
  uschar *saveline = s;
  uschar name[64];


  while (isspace(*s)) s++;
  if (*s == '!')
    {
    negated = TRUE;
    s++;
    }


  s = readconf_readname(name, sizeof(name), s);
  if (*s == ':' || (isupper(name[0]) && *s == '=')) return yield;


  if ((v = acl_checkname(name, verbs, nelem(verbs))) < 0)
    {
    if (this == NULL)
      {
      *error = string_sprintf("unknown ACL verb \"%s\" in \"%s\"", name,
        saveline);
      return NULL;
      }
    }


  else
    {
    if (negated)
      {
      *error = string_sprintf("malformed ACL line \"%s\"", saveline);
      return NULL;
      }
    this = store_get(sizeof(acl_block));
    *lastp = this;
    lastp = &(this->next);
    this->next = NULL;
    this->verb = v;
    this->condition = NULL;
    condp = &(this->condition);
    if (*s == 0) continue;
    if (*s == '!')
      {
      negated = TRUE;
      s++;
      }
    s = readconf_readname(name, sizeof(name), s);
    }


  if ((c = acl_checkcondition(name, conditions, nelem(conditions))) < 0)
    {
    *error = string_sprintf("unknown ACL condition/modifier in \"%s\"",
      saveline);
    return NULL;
    }


  if (negated && conditions[c].is_modifier)
    {
    *error = string_sprintf("ACL error: negation is not allowed with "
      "\"%s\"", conditions[c].name);
    return NULL;
    }


  if (c == ACLC_ENDPASS &&
      this->verb != ACL_ACCEPT &&
      this->verb != ACL_DISCARD)
    {
    *error = string_sprintf("ACL error: \"%s\" is not allowed with \"%s\"",
      conditions[c].name, verbs[this->verb]);
    return NULL;
    }

  cond = store_get(sizeof(acl_condition_block));
  cond->next = NULL;
  cond->type = c;
  cond->u.negated = negated;

  *condp = cond;
  condp = &(cond->next);


  if (c == ACLC_SET)
#ifndef DISABLE_DKIM
    if (  Ustrncmp(s, "dkim_verify_status", 18) == 0
       || Ustrncmp(s, "dkim_verify_reason", 18) == 0)
      {
      uschar * endptr = s+18;

      if (isalnum(*endptr))
	{
	*error = string_sprintf("invalid variable name after \"set\" in ACL "
	  "modifier \"set %s\" "
	  "(only \"dkim_verify_status\" or \"dkim_verify_reason\" permitted)",
	  s);
	return NULL;
	}
      cond->u.varname = string_copyn(s, 18);
      s = endptr;
      while (isspace(*s)) s++;
      }
    else
#endif
    {
    uschar *endptr;

    if (Ustrncmp(s, "acl_c", 5) != 0 &&
        Ustrncmp(s, "acl_m", 5) != 0)
      {
      *error = string_sprintf("invalid variable name after \"set\" in ACL "
        "modifier \"set %s\" (must start \"acl_c\" or \"acl_m\")", s);
      return NULL;
      }

    endptr = s + 5;
    if (!isdigit(*endptr) && *endptr != '_')
      {
      *error = string_sprintf("invalid variable name after \"set\" in ACL "
        "modifier \"set %s\" (digit or underscore must follow acl_c or acl_m)",
        s);
      return NULL;
      }

    while (*endptr != 0 && *endptr != '=' && !isspace(*endptr))
      {
      if (!isalnum(*endptr) && *endptr != '_')
        {
        *error = string_sprintf("invalid character \"%c\" in variable name "
          "in ACL modifier \"set %s\"", *endptr, s);
        return NULL;
        }
      endptr++;
      }

    cond->u.varname = string_copyn(s + 4, endptr - s - 4);
    s = endptr;
    while (isspace(*s)) s++;
    }


  if (c != ACLC_ENDPASS)
    {
    if (*s++ != '=')
      {
      *error = string_sprintf("\"=\" missing after ACL \"%s\" %s", name,
        conditions[c].is_modifier ? US"modifier" : US"condition");
      return NULL;
      }
    while (isspace(*s)) s++;
    cond->arg = string_copy(s);
    }
  }

return yield;
}
