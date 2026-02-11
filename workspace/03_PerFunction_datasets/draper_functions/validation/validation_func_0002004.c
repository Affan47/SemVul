mainwindow_connect_bookmark(GtkWidget *w, gpointer data) {
  HostBookmark *bm;
  char p[32];
  bm=(HostBookmark *)data;


  strcpy(p,"timeseal");
  global.chandler->openServer(bm->host,bm->port,new FicsProtocol(),
			      strcmp(bm->protocol,"FICS") ? 0 : p);
}
