url_parse (const char *url, int *error, struct iri *iri, bool percent_encode)
{
  struct url *u;
  const char *p;
  bool path_modified, host_modified;

  enum url_scheme scheme;
  const char *seps;

  const char *uname_b,     *uname_e;
  const char *host_b,      *host_e;
  const char *path_b,      *path_e;
  const char *params_b,    *params_e;
  const char *query_b,     *query_e;
  const char *fragment_b,  *fragment_e;

  int port;
  char *user = NULL, *passwd = NULL;

  const char *url_encoded = NULL;

  int error_code;

  scheme = url_scheme (url);
  if (scheme == SCHEME_INVALID)
    {
      if (url_has_scheme (url))
        error_code = PE_UNSUPPORTED_SCHEME;
      else
        error_code = PE_MISSING_SCHEME;
      goto error;
    }

  url_encoded = url;

  if (iri && iri->utf8_encode)
    {
      char *new_url = NULL;

      iri->utf8_encode = remote_to_utf8 (iri, iri->orig_url ? iri->orig_url : url, &new_url);
      if (!iri->utf8_encode)
        new_url = NULL;
      else
        {
          xfree (iri->orig_url);
          iri->orig_url = xstrdup (url);
          url_encoded = reencode_escapes (new_url);
          if (url_encoded != new_url)
            xfree (new_url);
          percent_encode = false;
        }
    }

  if (percent_encode)
    url_encoded = reencode_escapes (url);

  p = url_encoded;
  p += strlen (supported_schemes[scheme].leading_string);
  uname_b = p;
  p = url_skip_credentials (p);
  uname_e = p;


  path_b     = path_e     = NULL;
  params_b   = params_e   = NULL;
  query_b    = query_e    = NULL;
  fragment_b = fragment_e = NULL;


  seps = init_seps (scheme);

  host_b = p;

  if (*p == '[')
    {


      host_b = p + 1;
      host_e = strchr (host_b, ']');

      if (!host_e)
        {
          error_code = PE_UNTERMINATED_IPV6_ADDRESS;
          goto error;
        }

#ifdef ENABLE_IPV6

      if (!is_valid_ipv6_address(host_b, host_e))
        {
          error_code = PE_INVALID_IPV6_ADDRESS;
          goto error;
        }


      p = host_e + 1;
#else
      error_code = PE_IPV6_NOT_SUPPORTED;
      goto error;
#endif


      if (!strchr (seps, *p))
        {

          error_code = PE_INVALID_HOST_NAME;
          goto error;
        }
    }
  else
    {
      p = strpbrk_or_eos (p, seps);
      host_e = p;
    }
  ++seps;

  if (host_b == host_e)
    {
      error_code = PE_INVALID_HOST_NAME;
      goto error;
    }

  port = scheme_default_port (scheme);
  if (*p == ':')
    {
      const char *port_b, *port_e, *pp;


      ++p;
      port_b = p;
      p = strpbrk_or_eos (p, seps);
      port_e = p;


      if (port_b != port_e)
        for (port = 0, pp = port_b; pp < port_e; pp++)
          {
            if (!c_isdigit (*pp))
              {


                error_code = PE_BAD_PORT_NUMBER;
                goto error;
              }
            port = 10 * port + (*pp - '0');


            if (port > 0xffff)
              {
                error_code = PE_BAD_PORT_NUMBER;
                goto error;
              }
          }
    }


  ++seps;


#define GET_URL_PART(sepchar, var) do {                         \
  if (*p == sepchar)                                            \
    var##_b = ++p, var##_e = p = strpbrk_or_eos (p, seps);      \
  ++seps;                                                       \
} while (0)

  GET_URL_PART ('/', path);
  if (supported_schemes[scheme].flags & scm_has_params)
    GET_URL_PART (';', params);
  if (supported_schemes[scheme].flags & scm_has_query)
    GET_URL_PART ('?', query);
  if (supported_schemes[scheme].flags & scm_has_fragment)
    GET_URL_PART ('#', fragment);

#undef GET_URL_PART
  assert (*p == 0);

  if (uname_b != uname_e)
    {


      if (!parse_credentials (uname_b, uname_e - 1, &user, &passwd))
        {
          error_code = PE_INVALID_USER_NAME;
          goto error;
        }
    }

  u = xnew0 (struct url);
  u->scheme = scheme;
  u->host   = strdupdelim (host_b, host_e);
  u->port   = port;
  u->user   = user;
  u->passwd = passwd;

  u->path = strdupdelim (path_b, path_e);
  path_modified = path_simplify (scheme, u->path);
  split_path (u->path, &u->dir, &u->file);

  host_modified = lowercase_str (u->host);


  if (strchr (u->host, '%'))
    {
      url_unescape (u->host);
      host_modified = true;


      if (opt.enable_iri && iri)
        {
          char *new = idn_encode (iri, u->host);
          if (new)
            {
              xfree (u->host);
              u->host = new;
              u->idn_allocated = true;
              host_modified = true;
            }
        }
    }

  if (params_b)
    u->params = strdupdelim (params_b, params_e);
  if (query_b)
    u->query = strdupdelim (query_b, query_e);
  if (fragment_b)
    u->fragment = strdupdelim (fragment_b, fragment_e);

  if (opt.enable_iri || path_modified || u->fragment || host_modified || path_b == path_e)
    {


      u->url = url_string (u, URL_AUTH_SHOW);

      if (url_encoded != url)
        xfree (url_encoded);
    }
  else
    {
      if (url_encoded == url)
        u->url = xstrdup (url);
      else
        u->url = (char *) url_encoded;
    }

  return u;

 error:

  if (url_encoded && url_encoded != url)
    xfree (url_encoded);


  if (error)
    *error = error_code;
  return NULL;
}
