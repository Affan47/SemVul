unlock_scd (ctrl_t ctrl, int rc)
{
  if (gpg_err_code (rc) == GPG_ERR_NOT_OPERATIONAL
      && gpg_err_source (rc) == GPG_ERR_SOURCE_SCD)
    {


      assuan_transact (primary_scd_ctx, "BYE",
                       NULL, NULL, NULL, NULL, NULL, NULL);
    }

  if (ctrl->scd_local->locked != 1)
    {
      log_error ("unlock_scd: invalid lock count (%d)\n",
                 ctrl->scd_local->locked);
      if (!rc)
        rc = gpg_error (GPG_ERR_INTERNAL);
    }
  ctrl->scd_local->locked = 0;
  return rc;
}
