create_int_opts()
{

  GtkWidget *hbox = gtk_hbox_new (FALSE, 1);

  opt_int_opts = gtk_combo_box_new_text ();
  gtk_box_pack_start (GTK_BOX (hbox), opt_int_opts, FALSE, FALSE, 0);

  int i;
  for(i=0; i < int_selN; i++) {
    gtk_combo_box_append_text (GTK_COMBO_BOX_TEXT (opt_int_opts), int_sel[i].name);
  }

  gtk_combo_box_set_active (GTK_COMBO_BOX (opt_int_opts), current_intcode);
  g_signal_connect (G_OBJECT (opt_int_opts), "changed", G_CALLBACK (cb_select), NULL);

  return hbox;
}
