cmd_learn (assuan_context_t ctx, char *line)
{
  ctrl_t ctrl = assuan_get_pointer (ctx);
  int rc = 0;
  int only_keypairinfo = has_option (line, "--keypairinfo");

  if ((rc = open_card (ctrl, NULL)))
    return rc;


  if (!only_keypairinfo)
    {
      char *serial;
      time_t stamp;

      rc = app_get_serial_and_stamp (ctrl->app_ctx, &serial, &stamp);
      if (rc)
        return rc;

      rc = print_assuan_status (ctx, "SERIALNO", "%s %lu",
                                serial, (unsigned long)stamp);
      if (rc < 0)
        {
          xfree (serial);
          return out_of_core ();
        }

      if (!has_option (line, "--force"))
        {
          char *command;

          rc = gpgrt_asprintf (&command, "KNOWNCARDP %s %lu",
                               serial, (unsigned long)stamp);
          if (rc < 0)
            {
              xfree (serial);
              return out_of_core ();
            }
          rc = assuan_inquire (ctx, command, NULL, NULL, 0);
          xfree (command);
          if (rc)
            {
              if (gpg_err_code (rc) != GPG_ERR_ASS_CANCELED)
                log_error ("inquire KNOWNCARDP failed: %s\n",
                           gpg_strerror (rc));
              xfree (serial);
              return rc;
            }

        }
      xfree (serial);
    }


  if (!rc)
    rc = app_write_learn_status (ctrl->app_ctx, ctrl, only_keypairinfo);

  TEST_CARD_REMOVAL (ctrl, rc);
  return rc;
}
