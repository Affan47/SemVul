snddlg_picktheme(GtkMenuItem *w,gpointer data) {
  SoundEventDialog *me;
  EboardFileFinder eff;
  char z[512],zz[512];
  int i,j;

  me=(SoundEventDialog *)data;

  j=me->sthemes.size();

  for(i=0;i<j;i++)
    if (w == GTK_MENU_ITEM(me->sthemes[i])) {
      g_strlcpy(z,global.SoundFiles[i].c_str(),512);
      if (strlen(z)) {
	if (eff.find(z,zz))
	  strcpy(z,zz);
	gtk_entry_set_text(GTK_ENTRY(me->en[3]),z);
	gtset(GTK_TOGGLE_BUTTON(me->rd[1]),TRUE);
      }
      return;
    }
}
