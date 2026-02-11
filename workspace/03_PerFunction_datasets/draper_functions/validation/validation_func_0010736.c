open_this_file (GtkWidget * widget, char *name)
{
  int i, tot;
  char *t;

  if (check_p)
    {

      tot = gtk_notebook_get_n_pages (GTK_NOTEBOOK (notebook->notebook));

      for (i = 0; i < tot; ++i)
        {
          if (!(file[i]->name))
            {
              continue;
            }

          if (!strcmp (file[i]->name, name))
            {


              gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook->notebook), i);

              return NULL;
            }
        }

      t = g_path_get_basename (name);
      make_new_notebook_page (t);
      g_free (t);
    }
  else
    {
      check_p = TRUE;
    }

  _ncurrent (file)->name = (char *) name;
  file_open (NULL);

  gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook->notebook), notebook->current);

  return NULL;
}
