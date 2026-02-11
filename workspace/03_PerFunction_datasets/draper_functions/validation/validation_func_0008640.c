dacs_cookie_zap(request_rec *r, char *cookie_str)
{
  char *p, *q;
  dacs_server_config *sc_rec
	= (dacs_server_config *)
	ap_get_module_config(r->server->module_config, &auth_dacs_module);


  q = p = cookie_str;
  while (1) {
	if (!is_dacs_cookie(p)) {
	  if (q != cookie_str) {

		*q++ = ';';
		*q++ = ' ';
	  }


	  while (*p != '\0' && *p != ';')
		*q++ = *p++;


	  if (*p == '\0')
		break;


	  p++;
	  while (*p == ' ')
		p++;

	  if (*p == '\0')
		break;
	}
	else {

	  if (debug_enabled(sc_rec))
		ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
					 "mod_auth_dacs: dacs_cookie_zap: deleting DACS cookie");
	  if ((p = skip_cookie(p)) == NULL)
		break;
	}
  }
  *q = '\0';
}
