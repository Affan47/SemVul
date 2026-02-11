app_getattr (app_t app, ctrl_t ctrl, const char *name)
{
  gpg_error_t err;

  if (!app || !name || !*name)
    return gpg_error (GPG_ERR_INV_VALUE);
  if (!app->ref_count)
    return gpg_error (GPG_ERR_CARD_NOT_INITIALIZED);

  if (app->apptype && name && !strcmp (name, "APPTYPE"))
    {
      send_status_info (ctrl, "APPTYPE",
                        app->apptype, strlen (app->apptype), NULL, 0);
      return 0;
    }
  if (name && !strcmp (name, "SERIALNO"))
    {
      char *serial;
      time_t stamp;
      int rc;

      rc = app_get_serial_and_stamp (app, &serial, &stamp);
      if (rc)
        return rc;
      send_status_info (ctrl, "SERIALNO", serial, strlen (serial), NULL, 0);
      xfree (serial);
      return 0;
    }

  if (!app->fnc.getattr)
    return gpg_error (GPG_ERR_UNSUPPORTED_OPERATION);
  err = lock_reader (app->slot, ctrl);
  if (err)
    return err;
  err =  app->fnc.getattr (app, ctrl, name);
  unlock_reader (app->slot);
  return err;
}
