randomize_password(struct w *widgets)
{
    char *rnd_string;
    int len;
    gchar *info;
    gchar *utf8=NULL;
    char *default_password_length;


    default_password_length = allocate(100);

    snprintf(default_password_length, 10, "%s", MIN_PASS_LEN);

    if( chars_are_digits(default_password_length) )
    {
	if( strlen(default_password_length) < 4 )
	  len = atoi(default_password_length);
	else
	  {
	     info = g_strdup_printf(_("Max randomize password length is 999\n"));
	     show_info(info);
	     g_free(info);
	     free(default_password_length);
	     return;
	  }
    }
    else
      {
	 info = g_strdup_printf(_("Randomize password length can only contain digits\n"));
	 show_info(info);
	 g_free(info);
	 free(default_password_length);
         return;
      }

    rnd_string = random_string(len);

    free(default_password_length);


    utf8 = g_locale_to_utf8(rnd_string, strlen(rnd_string), NULL, NULL, NULL);
    gtk_entry_set_text(GTK_ENTRY(widgets->user_set_entry[1]), utf8);
    if( utf8!=NULL )
      g_free(utf8);

    free(rnd_string);
}
