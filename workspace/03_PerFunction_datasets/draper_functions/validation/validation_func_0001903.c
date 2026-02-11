driversetup_update_clicked (GtkWidget *widget, TDRIVERSETUP *driversetup_t)
{
  char *data[2];
  int i;

  if (driversetup_t)
    {
      data[0] = gtk_entry_get_text (GTK_ENTRY (driversetup_t->key_entry));
      if (STRLEN (data[0]))
	{
	  data[1] = gtk_entry_get_text (GTK_ENTRY (driversetup_t->value_entry));

	  if (GTK_CLIST (driversetup_t->key_list)->selection != NULL)
	    i = GPOINTER_TO_INT (GTK_CLIST (driversetup_t->key_list)->selection->
		data);
	  else
	    i = 0;


	  if (i < GTK_CLIST (driversetup_t->key_list)->rows)
	    {
	      gtk_clist_set_text (GTK_CLIST (driversetup_t->key_list), i, 0,
		  data[0]);
	      gtk_clist_set_text (GTK_CLIST (driversetup_t->key_list), i, 1,
		  data[1]);
	    }
	}

      gtk_entry_set_text (GTK_ENTRY (driversetup_t->key_entry), "");
      gtk_entry_set_text (GTK_ENTRY (driversetup_t->value_entry), "");
    }
}
