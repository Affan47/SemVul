eebmd_rmall(GtkWidget *w, gpointer data)
{
  list<EngineBookmark *>::iterator ei;
  EEBMDp me;

  me=(EEBMDp) data;

  for(ei=global.EnginePresets.begin();ei!=global.EnginePresets.end();ei++)
    delete(*ei);

  global.EnginePresets.clear();

  global.writeRC();

  me->refresh();
  me->updateRightPane();
}
