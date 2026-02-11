get_profile(metro_t* metro,
                               int n, char** option_name)
{
  static gchar* name = NULL;
  gchar* value = NULL;

  int profile_n = n / 4;
  int suboption_n = n % 4;

  GtkListStore* store;

  gchar* name_prefix = option_name ? *option_name : "Profile_";
  gchar* name_suffix = "";

  if (name) {
    g_free(name);
    name = NULL;
  }

  if ((store =
        GTK_LIST_STORE(gtk_tree_view_get_model(metro->profiles_tree))))
  {
    GtkTreeIter iter;

    if (gtk_tree_model_iter_nth_child(
          GTK_TREE_MODEL(store), &iter, NULL, profile_n))
    {
      profile_t* profile;
      gchar* s;
      gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
                         COLUMN_NAME, &s,
                         COLUMN_PROFILE, &profile,
			 -1);
      switch (suboption_n) {
        case 0:
          name_suffix = "Name";
	  value = s;
          break;
        case 1:
          name_suffix = "Speed";
	  value = profile_get_speed(profile);
          break;
        case 2:
          name_suffix = "Meter";
	  value = profile_get_meter(profile);
          break;
        case 3:
          name_suffix = "Accents";
	  value = profile_get_accents(profile);
          break;
        default:
          g_print("get_profile(): unhandled suboption: %d.\n", suboption_n);
      }

      name = g_strdup_printf("%s%d_%s", name_prefix, profile_n + 1, name_suffix);

      if (option_name)
        *option_name = name;

    } else g_print("get_profile(): No profile #%d available.\n", profile_n);
  } else g_print("get_profile(): No tree model available.\n");

  return value;
}
