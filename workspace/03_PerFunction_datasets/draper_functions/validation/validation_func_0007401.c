smtp_auth_plain_get_password (GoaSmtpAuthPlain  *auth,
                              GCancellable      *cancellable,
                              GError           **error)
{
  gchar *password;

  password = NULL;

  if (auth->password != NULL)
    {
      password = g_strdup (auth->password);
    }
  else if (auth->provider != NULL && auth->object != NULL)
    {
      GVariant *credentials;
      credentials = goa_utils_lookup_credentials_sync (auth->provider,
                                                       auth->object,
                                                       cancellable,
                                                       error);
      if (credentials == NULL)
        {
          g_prefix_error (error, "Error looking up credentials for SMTP PLAIN in keyring: ");
          goto out;
        }
      if (!g_variant_lookup (credentials, "smtp-password", "s", &password))
        {
          g_set_error (error,
                       GOA_ERROR,
                       GOA_ERROR_FAILED,
                       _("Did not find smtp-password in credentials"));
          g_variant_unref (credentials);
          goto out;
        }
      g_variant_unref (credentials);
    }
  else
    {
      g_set_error (error,
                   GOA_ERROR,
                   GOA_ERROR_FAILED,
                   _("Cannot do SMTP PLAIN without a password"));
      goto out;
    }

 out:
  return password;
}
