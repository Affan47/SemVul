qb_shortcut(GtkWidget *w, gpointer data) {
  int *v;
  char z[2048],y[2048],a[2048];
  tstring t;
  string *p;

  v=(int *) data;

  if (global.QuickbarButtons[*v] != 0) {
    g_strlcpy(z, global.QuickbarButtons[*v]->command.c_str(), 256);

    if (global.protocol == 0) return;
    if (global.network == 0) return;
    if (!global.network->isConnected()) return;

    if (strstr(z,"script.") == z) {
      strcpy(y,z+7);
      snprintf(a,2048,_("> [script run from shortcut] %s"),y);
      global.output->append(a, global.SelfInputColor);
      new ScriptInstance(y);
      return;
    }

    t.set(z);
    while((p=t.token(";"))!=0) {
      g_strlcpy(y,p->c_str(),2048);
      global.protocol->sendUserInput(y);
      g_strlcpy(y,_("> [issued from shortcut] "),2048);
      g_strlcat(y,p->c_str(),2048);
      global.output->append(y, global.SelfInputColor);
    }

  }
}
