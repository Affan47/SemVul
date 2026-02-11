gtk_settings_get_value(char *name,gpointer thesettings[])
{
  int lp=GTKSETTINGS_HEADERSIZE;
  while( thesettings[lp]) {
    if(strcmp(name,thesettings[lp])==0) {


      return GPOINTER_TO_INT(thesettings[lp+1]);

    }
    lp+=GTKSETTINGS_BLOCKS_SIZE;
  }
  g_warning("gtk_settings_get_value: setting '%s' not found", name);

  return 0;
}
