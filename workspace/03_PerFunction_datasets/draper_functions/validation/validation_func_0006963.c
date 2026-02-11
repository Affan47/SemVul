check_mysql_auth_require(char *user, const char *t, request_rec *r)
{
	mysql_auth_config_rec *sec = (mysql_auth_config_rec *) ap_get_module_config(r->per_dir_config, &auth_mysql_module);
	const char *w;
	int rv;

	w = ap_getword(r->pool, &t, ' ');


	if (!strcmp(w, "valid-user")) {
		return OK;
	}


	if (!strcmp(w, "user")) {
		while (t[0]) {
			w = ap_getword_conf(r->pool, &t);
			if (!strcmp(user, w)) {
				return OK;
			}
		}

		return HTTP_UNAUTHORIZED;
	} else if (!strcmp(w, "group")) {


		while (t[0])
		{
			w = ap_getword_conf(r->pool, &t);
			rv = mysql_check_group(r, user, (char *)w, sec);

			if (rv == 1)
			{

				return OK;
			}
			else if (rv == -1)
			{
				return HTTP_INTERNAL_SERVER_ERROR;
			}
		}

		return HTTP_UNAUTHORIZED;
	}
	else
	{
		APACHELOG(APLOG_ERR, r, "Invalid argument to require: %s", w);
		return HTTP_INTERNAL_SERVER_ERROR;
	}

	APACHELOG(APLOG_ERR, r, "CAN'T HAPPEN: Dropped out of the bottom of check_mysql_auth_require!");
	return HTTP_INTERNAL_SERVER_ERROR;
}
