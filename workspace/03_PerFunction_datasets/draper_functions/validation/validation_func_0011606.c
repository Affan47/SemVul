varcircles_get_nth (gint which, gint jvar, GGobiData * d)
{
  GtkWidget *w = NULL;

  switch (which) {
  case VB:
    w = (GtkWidget *) g_slist_nth_data (d->vcirc_ui.vb, jvar);
    break;
  case LBL:
    w = (GtkWidget *) g_slist_nth_data (d->vcirc_ui.label, jvar);
    break;
  case DA:
    w = (GtkWidget *) g_slist_nth_data (d->vcirc_ui.da, jvar);
    break;
  default:
    break;
  }

  return w;
}
