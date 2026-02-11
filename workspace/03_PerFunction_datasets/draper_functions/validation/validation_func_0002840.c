get_tokens_sync (GoaOAuthProvider  *provider,
                 const gchar       *token,
                 const gchar       *token_secret,
                 const gchar       *session_handle,
                 const gchar       *verifier,
                 gchar            **out_access_token_secret,
                 gint              *out_access_token_expires_in,
                 gchar            **out_session_handle,
                 gint              *out_session_handle_expires_in,
                 GCancellable      *cancellable,
                 GError           **error)
{
  RestProxy *proxy;
  RestProxyCall *call;
  gchar *ret;
  guint status_code;
  GHashTable *f;
  const gchar *expires_in_str;
  gchar *ret_access_token;
  gchar *ret_access_token_secret;
  gint ret_access_token_expires_in;
  gchar *ret_session_handle;
  gint ret_session_handle_expires_in;

  ret = NULL;
  ret_access_token = NULL;
  ret_access_token_secret = NULL;
  ret_access_token_expires_in = 0;
  ret_session_handle = NULL;
  ret_session_handle_expires_in = 0;

  proxy = oauth_proxy_new (goa_oauth_provider_get_consumer_key (provider),
                           goa_oauth_provider_get_consumer_secret (provider),
                           goa_oauth_provider_get_token_uri (provider),
                           FALSE);
  oauth_proxy_set_token (OAUTH_PROXY (proxy), token);
  oauth_proxy_set_token_secret (OAUTH_PROXY (proxy), token_secret);
  call = rest_proxy_new_call (proxy);
  rest_proxy_call_set_method (call, "POST");
  if (verifier != NULL)
    rest_proxy_call_add_param (call, "oauth_verifier", verifier);
  if (session_handle != NULL)
    rest_proxy_call_add_param (call, "oauth_session_handle", session_handle);

  if (!rest_proxy_call_sync (call, error))
    goto out;

  status_code = rest_proxy_call_get_status_code (call);
  if (status_code != 200)
    {
      g_set_error (error,
                   GOA_ERROR,
                   GOA_ERROR_FAILED,

                   _("Expected status 200 when requesting access token, instead got status %d (%s)"),
                   status_code,
                   rest_proxy_call_get_status_message (call));
      goto out;
    }

  f = soup_form_decode (rest_proxy_call_get_payload (call));
  ret_access_token = g_strdup (g_hash_table_lookup (f, "oauth_token"));
  ret_access_token_secret = g_strdup (g_hash_table_lookup (f, "oauth_token_secret"));
  ret_session_handle = g_strdup (g_hash_table_lookup (f, "oauth_session_handle"));
  expires_in_str = g_hash_table_lookup (f, "oauth_expires_in");
  if (expires_in_str != NULL)
    ret_access_token_expires_in = atoi (expires_in_str);
  expires_in_str = g_hash_table_lookup (f, "oauth_authorization_expires_in");
  if (expires_in_str != NULL)
    ret_session_handle_expires_in = atoi (expires_in_str);
  g_hash_table_unref (f);

  if (ret_access_token == NULL || ret_access_token_secret == NULL)
    {
      g_set_error (error,
                   GOA_ERROR,
                   GOA_ERROR_FAILED,
                   _("Missing access_token or access_token_secret headers in response"));
      goto out;
    }

  ret = ret_access_token; ret_access_token = NULL;
  if (out_access_token_secret != NULL)
    {
      *out_access_token_secret = ret_access_token_secret;
      ret_access_token_secret = NULL;
    }
  if (out_access_token_expires_in != NULL)
    *out_access_token_expires_in = ret_access_token_expires_in;
  if (out_session_handle != NULL)
    {
      *out_session_handle = ret_session_handle;
      ret_session_handle = NULL;
    }
  if (out_session_handle_expires_in != NULL)
    *out_session_handle_expires_in = ret_session_handle_expires_in;

 out:
  g_free (ret_access_token);
  g_free (ret_access_token_secret);
  g_free (ret_session_handle);
  if (call != NULL)
    g_object_unref (call);
  if (proxy != NULL)
    g_object_unref (proxy);
  return ret;
}
