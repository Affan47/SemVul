_complete_auth_cb (GObject *object, GAsyncResult *result, gpointer data)
{
  FspSession *session = NULL;
  CancellableOperationData *co_data = NULL;
  FrogrController *controller = NULL;
  FrogrControllerPrivate *priv = NULL;
  FspDataAuthToken *auth_token = NULL;
  GError *error = NULL;

  session = FSP_SESSION (object);
  co_data = (CancellableOperationData*) data;
  controller = co_data->controller;
  priv = FROGR_CONTROLLER_GET_PRIVATE (controller);

  auth_token = fsp_session_complete_auth_finish (session, result, &error);
  if (auth_token)
    {
      if (auth_token->token)
        {
          FrogrAccount *account = NULL;


          account = frogr_account_new_full (auth_token->token, auth_token->token_secret);
          frogr_account_set_id (account, auth_token->nsid);
          frogr_account_set_username (account, auth_token->username);
          frogr_account_set_fullname (account, auth_token->fullname);


          frogr_account_set_permissions (account, "write");


          _set_active_account (controller, account);

          DEBUG ("%s", "Authorization successfully completed!");
        }

      fsp_data_free (FSP_DATA (auth_token));
    }

  if (error != NULL)
    {
      _handle_flicksoup_error (controller, error, TRUE);
      DEBUG ("Authorization failed: %s", error->message);
      g_error_free (error);
    }

  frogr_main_view_hide_progress (priv->mainview);

  _clear_cancellable (controller, co_data->cancellable);
  g_slice_free (CancellableOperationData, co_data);

  priv->fetching_auth_token = FALSE;
}
