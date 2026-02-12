open_card (ctrl_t ctrl, const char *apptype)
{
  gpg_error_t err;
  int vrdr;


  if (ctrl->server_local->card_removed)
    return gpg_error (GPG_ERR_CARD_REMOVED);

  if ( IS_LOCKED (ctrl) )
    return gpg_error (GPG_ERR_LOCKED);


  if (ctrl->server_local->app_ctx_marked_for_release)
    {
      ctrl->server_local->app_ctx_marked_for_release = 0;
      release_application (ctrl->app_ctx);
      ctrl->app_ctx = NULL;
    }


  if (ctrl->app_ctx)
    {
      return check_application_conflict
        (ctrl, vreader_slot (ctrl->server_local->vreader_idx), apptype);
    }


  if (ctrl->server_local->vreader_idx != -1)
    vrdr = ctrl->server_local->vreader_idx;
  else
    vrdr = get_current_reader ();
  ctrl->server_local->vreader_idx = vrdr;
  if (vrdr == -1)
    err = gpg_error (GPG_ERR_CARD);
  else
    {


      int sw;
      int slot = vreader_slot (vrdr);

      ctrl->server_local->disconnect_allowed = 0;
      sw = apdu_connect (slot);
      if (sw && sw != SW_HOST_ALREADY_CONNECTED)
        {
          if (sw == SW_HOST_NO_CARD)
            err = gpg_error (GPG_ERR_CARD_NOT_PRESENT);
          else if (sw == SW_HOST_CARD_INACTIVE)
            err = gpg_error (GPG_ERR_CARD_RESET);
          else
            err = gpg_error (GPG_ERR_CARD);
	}
      else
        err = select_application (ctrl, slot, apptype, &ctrl->app_ctx);
    }

  TEST_CARD_REMOVAL (ctrl, err);
  return err;
}
