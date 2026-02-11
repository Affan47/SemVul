agent_get_confirmation (ctrl_t ctrl,
                        const char *desc, const char *ok,
                        const char *notok, int with_cancel)
{
  int rc;
  char line[ASSUAN_LINELENGTH];

  rc = start_pinentry (ctrl);
  if (rc)
    return rc;

  if (desc)
    snprintf (line, DIM(line)-1, "SETDESC %s", desc);
  else
    snprintf (line, DIM(line)-1, "RESET");
  line[DIM(line)-1] = 0;
  rc = assuan_transact (entry_ctx, line, NULL, NULL, NULL, NULL, NULL, NULL);


  if (rc && gpg_err_source (rc) && gpg_err_code (rc) == GPG_ERR_ASS_CANCELED)
    rc = gpg_err_make (gpg_err_source (rc), GPG_ERR_CANCELED);

  if (rc)
    return unlock_pinentry (rc);

  if (ok)
    {
      snprintf (line, DIM(line)-1, "SETOK %s", ok);
      line[DIM(line)-1] = 0;
      rc = assuan_transact (entry_ctx,
                            line, NULL, NULL, NULL, NULL, NULL, NULL);
      if (rc)
        return unlock_pinentry (rc);
    }
  if (notok)
    {


      if (with_cancel)
        {
          snprintf (line, DIM(line)-1, "SETNOTOK %s", notok);
          line[DIM(line)-1] = 0;
          rc = assuan_transact (entry_ctx,
                                line, NULL, NULL, NULL, NULL, NULL, NULL);
        }
      else
        rc = GPG_ERR_ASS_UNKNOWN_CMD;

      if (gpg_err_code (rc) == GPG_ERR_ASS_UNKNOWN_CMD)
	{
	  snprintf (line, DIM(line)-1, "SETCANCEL %s", notok);
	  line[DIM(line)-1] = 0;
	  rc = assuan_transact (entry_ctx, line,
                                NULL, NULL, NULL, NULL, NULL, NULL);
	}
      if (rc)
        return unlock_pinentry (rc);
    }

  rc = assuan_transact (entry_ctx, "CONFIRM",
                        NULL, NULL, NULL, NULL, NULL, NULL);
  if (rc && gpg_err_source (rc) && gpg_err_code (rc) == GPG_ERR_ASS_CANCELED)
    rc = gpg_err_make (gpg_err_source (rc), GPG_ERR_CANCELED);

  return unlock_pinentry (rc);
}
