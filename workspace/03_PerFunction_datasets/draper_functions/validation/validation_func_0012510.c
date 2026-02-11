change_spin_cb(GtkSpinButton * spin_button, gpointer data) {

  gdouble temp_val;
  gint which_widget;
  GtkWidget * dialog = data;
  ui_time_dialog_t * td;
  GtkTreeSelection *selection;
  GtkTreeModel * model;


  which_widget = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(spin_button), "type"));
  td = g_object_get_data(G_OBJECT(dialog), "td");

  temp_val = gtk_spin_button_get_value(spin_button);

  switch(which_widget) {
  case ENTRY_START:
    if (temp_val-EPSILON*fabs(temp_val) > td->end)
      td->start = td->end-EPSILON*fabs(td->end);
    else
      td->start = temp_val;
    break;
  case ENTRY_END:
    if (temp_val+EPSILON*fabs(temp_val) < td->start)
      td->end = td->start+EPSILON*fabs(td->start);
    else
      td->end = temp_val;
    break;
  }

  model = gtk_tree_view_get_model(GTK_TREE_VIEW(td->tree_view));
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(td->tree_view));
  update_selections(model, selection, dialog, td);
  update_entries(dialog, td);

  amitk_study_set_view_start_time(td->study, td->start);
  amitk_study_set_view_duration(td->study, td->end-td->start);

  return;
}
