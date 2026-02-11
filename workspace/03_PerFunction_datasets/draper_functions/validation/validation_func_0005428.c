fdriverchooser_finish_clicked (GtkWidget *widget, TFDRIVERCHOOSER *choose_t)
{
  char *szDriver;
  char *dsn;
  char buff[1024];

  if (choose_t)
    {
      if (GTK_CLIST (choose_t->driverlist)->selection != NULL)
	{
	  gtk_clist_get_text (GTK_CLIST (choose_t->driverlist),
	      GPOINTER_TO_INT (GTK_CLIST (choose_t->driverlist)->selection->
		  data), 0, &szDriver);
	  choose_t->driver = dm_SQL_A2W(szDriver, SQL_NTS);
	}
      else
	choose_t->driver = NULL;

      dsn = gtk_entry_get_text(choose_t->dsn_entry);
      if (strchr(dsn, '/') != NULL)
        snprintf(buff, sizeof(buff), "%s", dsn);
      else
        snprintf(buff, sizeof(buff), "%s/%s", choose_t->curr_dir, dsn);

      choose_t->dsn = strdup(buff);
      choose_t->driverlist = NULL;
      choose_t->dsn_entry = NULL;
      choose_t->b_back = NULL;
      choose_t->b_continue = NULL;
      choose_t->mess_entry = NULL;
      choose_t->tab_panel = NULL;
      choose_t->browse_sel = NULL;

      choose_t->ok = (choose_t->driver ? TRUE : FALSE);

      gtk_signal_disconnect_by_func (GTK_OBJECT (choose_t->mainwnd),
	  GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
      gtk_main_quit ();
      gtk_widget_destroy (choose_t->mainwnd);
    }
}
