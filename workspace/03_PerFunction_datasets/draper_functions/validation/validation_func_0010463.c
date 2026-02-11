object_picker(ui_study_t * ui_study, AmitkStudy * import_study) {

  GtkWidget * dialog;
  gchar * temp_string;
  GtkWidget * table;
  guint table_row;
  GtkWidget * tree_view;
  GtkWidget * scrolled;
  GList * selected_objects;
  GList * temp_objects;
  gint return_val;


  amitk_object_set_selected(AMITK_OBJECT(import_study), FALSE, AMITK_SELECTION_ALL);

  temp_string = g_strdup_printf(_("%s: Pick Object(s) to Import"), PACKAGE);
  dialog = gtk_dialog_new_with_buttons (temp_string,  ui_study->window,
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_EXECUTE, AMITK_RESPONSE_EXECUTE,
					GTK_STOCK_CANCEL, GTK_RESPONSE_CLOSE, NULL);
  gtk_window_set_title(GTK_WINDOW(dialog), temp_string);
  g_free(temp_string);


  g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(ui_common_init_dialog_response_cb), NULL);

  gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);


  table = gtk_table_new(5,2,FALSE);
  table_row=0;
  gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), table);

  tree_view = amitk_tree_view_new(AMITK_TREE_VIEW_MODE_MULTIPLE_SELECTION,NULL, NULL);
  g_object_set_data(G_OBJECT(dialog), "tree_view", tree_view);
  amitk_tree_view_set_study(AMITK_TREE_VIEW(tree_view), import_study);
  amitk_tree_view_expand_object(AMITK_TREE_VIEW(tree_view), AMITK_OBJECT(import_study));


  scrolled = gtk_scrolled_window_new(NULL,NULL);
  gtk_widget_set_size_request(scrolled,250,250);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
				 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled),
					tree_view);
  gtk_table_attach(GTK_TABLE(table), scrolled, 0,2,
		   table_row, table_row+1,GTK_FILL, GTK_FILL | GTK_EXPAND, X_PADDING, Y_PADDING);
  table_row++;


  gtk_widget_show_all(dialog);


  return_val = gtk_dialog_run(GTK_DIALOG(dialog));


  selected_objects = ui_common_init_dialog_selected_objects(dialog);
  gtk_widget_destroy(dialog);


  if (return_val == AMITK_RESPONSE_EXECUTE) {
    temp_objects = selected_objects;
    while (temp_objects != NULL) {
      amitk_object_remove_child(AMITK_OBJECT(import_study), AMITK_OBJECT(temp_objects->data));
      amitk_object_add_child(AMITK_OBJECT(ui_study->study), AMITK_OBJECT(temp_objects->data));
      temp_objects = temp_objects->next;
    }
  }
  selected_objects = amitk_objects_unref(selected_objects);

}
