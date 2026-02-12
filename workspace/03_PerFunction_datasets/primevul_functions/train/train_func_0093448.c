flatpak_dir_check_parental_controls (FlatpakDir    *self,
                                     const char    *ref,
                                     GBytes        *deploy_data,
                                     GCancellable  *cancellable,
                                     GError       **error)
{
#ifdef HAVE_LIBMALCONTENT
#ifdef USE_SYSTEM_HELPER
  g_autoptr(GError) local_error = NULL;
  const char *on_session = g_getenv ("FLATPAK_SYSTEM_HELPER_ON_SESSION");
  g_autoptr(GDBusConnection) dbus_connection = NULL;
  g_autoptr(MctManager) manager = NULL;
  g_autoptr(MctAppFilter) app_filter = NULL;
  const char *content_rating_type;
  g_autoptr(GHashTable) content_rating = NULL;
  g_autoptr(AutoPolkitAuthority) authority = NULL;
  g_autoptr(AutoPolkitDetails) details = NULL;
  g_autoptr(AutoPolkitSubject) subject = NULL;
  gint subject_uid;
  g_autoptr(AutoPolkitAuthorizationResult) result = NULL;
  gboolean authorized;
  gboolean repo_installation_allowed, app_is_appropriate;


  if (getuid () == 0)
    return TRUE;


  if (!g_str_has_prefix (ref, "app/"))
    return TRUE;

  g_debug ("Getting parental controls details for %s from %s",
           ref, flatpak_deploy_data_get_origin (deploy_data));

  if (on_session != NULL)
    {


      g_debug ("Skipping parental controls check for %s since the "
               "system bus is unavailable in the test environment", ref);
      return TRUE;
    }

  dbus_connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, cancellable, &local_error);
  if (dbus_connection == NULL)
    {
      g_propagate_error (error, g_steal_pointer (&local_error));
      return FALSE;
    }

  if (self->user || self->source_pid == 0)
    subject = polkit_unix_process_new_for_owner (getpid (), 0, getuid ());
  else
    subject = polkit_unix_process_new_for_owner (self->source_pid, 0, -1);


  subject_uid = polkit_unix_process_get_uid (POLKIT_UNIX_PROCESS (subject));
  if (subject_uid == -1)
    {
      g_set_error_literal (error, G_DBUS_ERROR, G_DBUS_ERROR_AUTH_FAILED,
                           "Failed to get subject UID");
      return FALSE;
    }

  manager = mct_manager_new (dbus_connection);
  app_filter = mct_manager_get_app_filter (manager, subject_uid,
                                           MCT_GET_APP_FILTER_FLAGS_INTERACTIVE,
                                           cancellable, &local_error);
  if (g_error_matches (local_error, MCT_APP_FILTER_ERROR, MCT_APP_FILTER_ERROR_DISABLED))
    {
      g_debug ("Skipping parental controls check for %s since parental "
               "controls are disabled globally", ref);
      return TRUE;
    }
  else if (g_error_matches (local_error, G_DBUS_ERROR, G_DBUS_ERROR_SERVICE_UNKNOWN) ||
           g_error_matches (local_error, G_DBUS_ERROR, G_DBUS_ERROR_NAME_HAS_NO_OWNER))
    {
      g_debug ("Skipping parental controls check for %s since a required "
               "service was not found", ref);
      return TRUE;
    }
  else if (local_error != NULL)
    {
      g_propagate_error (error, g_steal_pointer (&local_error));
      return FALSE;
    }


  repo_installation_allowed = ((self->user && mct_app_filter_is_user_installation_allowed (app_filter)) ||
                               (!self->user && mct_app_filter_is_system_installation_allowed (app_filter)));

  content_rating_type = flatpak_deploy_data_get_appdata_content_rating_type (deploy_data);
  content_rating = flatpak_deploy_data_get_appdata_content_rating (deploy_data);
  app_is_appropriate = flatpak_oars_check_rating (content_rating, content_rating_type,
                                                  app_filter);

  if (repo_installation_allowed && app_is_appropriate)
    {
      g_debug ("Parental controls policy satisfied for %s", ref);
      return TRUE;
    }


  authority = polkit_authority_get_sync (NULL, error);
  if (authority == NULL)
    return FALSE;

  result = polkit_authority_check_authorization_sync (authority, subject,
                                                      "org.freedesktop.Flatpak.override-parental-controls",
                                                      NULL,
                                                      POLKIT_CHECK_AUTHORIZATION_FLAGS_ALLOW_USER_INTERACTION,
                                                      cancellable, error);
  if (result == NULL)
    return FALSE;

  authorized = polkit_authorization_result_get_is_authorized (result);

  if (!authorized)
    return flatpak_fail_error (error, FLATPAK_ERROR_PERMISSION_DENIED,

                               _("Installing %s is not allowed by the policy set by your administrator"),
                               ref);

  g_debug ("Parental controls policy overridden by polkit for %s", ref);
#endif
#endif

  return TRUE;
}
