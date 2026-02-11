db_attr_add(void *hv, char *key, globus_rls_obj_type_t objtype,
	    globus_rls_attr_type_t type, char *name, char *sval, char *errmsg)

{
  db_handle_t			*h = (db_handle_t *) hv;
  char				buf[BIGBUF];
  SQLRETURN			r;
  int				rc;
  SQLINTEGER		attr_id;
  globus_rls_attr_type_t	atype;
  SQLINTEGER		obj_id;
  char				*valtab;
  char				dbuf[100];

  if (loglevel > 1)
    logit(LOG_DEBUG, "db_attr_add: %s %d %d %s %s", key, objtype, type,
	  name, sval);

  if (type == globus_rls_attr_type_str && strlen(sval) + 1 > MAXDBSTR) {
    strncpy(errmsg, sval, MAXERRMSG);
    return GLOBUS_RLS_BADARG;
  }

  begintran(h, NULL);

  rc = attrinfo(h, objtype, name, key, &attr_id, &atype, &obj_id, &valtab,
		errmsg);
  if (rc != GLOBUS_RLS_SUCCESS)
    goto error;


  if (atype != type) {
    sprintf(errmsg, "specified %d should be %d", type, atype);
    rc = GLOBUS_RLS_INV_ATTR_TYPE;
    goto error;
  }

  switch (type) {
    case globus_rls_attr_type_date:
      snprintf(buf, BIGBUF,
	       "insert into %s (obj_id, attr_id, value) values(%d, %d, %s)",
	       valtab, (int) obj_id, (int) attr_id, todate(sval, dbuf));
      break;
    case globus_rls_attr_type_flt:
      snprintf(buf, BIGBUF,
	       "insert into %s (obj_id, attr_id, value) values(%d, %d, %f)",
	       valtab, (int) obj_id, (int) attr_id, atof(sval));
      break;
    case globus_rls_attr_type_int:
      snprintf(buf, BIGBUF,
	      "insert into %s (obj_id, attr_id, value) values(%d, %d, %d)",
	       valtab, (int) obj_id, (int) attr_id, atoi(sval));
      break;
    case globus_rls_attr_type_str:
      snprintf(buf, BIGBUF,
	       "insert into %s (obj_id, attr_id, value) values(%d, %d, '%s')",
	       valtab, (int) obj_id, (int) attr_id, sval);
      break;
  }
  r = SQLExecDirect(h->stmt, (SQLCHAR *) buf, SQL_NTS);
  if (!SQLOK(r)) {
    rc = seterr_insertattr(h, r, valtab, (int) obj_id, (int) attr_id,
            GLOBUS_RLS_ATTR_EXIST, errmsg);
    goto error;
  }

  return endtran(h, SQL_COMMIT, errmsg, NULL);

 error:
  endtran(h, SQL_ROLLBACK, NULL, NULL);
  return rc;
}
