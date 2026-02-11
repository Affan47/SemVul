DialogueDelete(GtkWidget *w)
{
  GtkWidget *Dialogue;
  GtkWidget *Label;
  GtkWidget *Bouton;
  GtkWidget *frame, *vboxframe;


  if (NRatoms <1)
  {
    Message(_(" No Atom to delete !"),_("Warning"),TRUE);
    return ;
  }
    if (atoi(pathSelectedAtom) <0)
  {
    Message(_(" Please Select Your Atom to delete!"),_("Warning"),TRUE);
    return ;
  }


  Dialogue = gtk_dialog_new();
  gtk_window_set_title(GTK_WINDOW(Dialogue),_("Delete Atom"));
  gtk_window_set_modal (GTK_WINDOW (Dialogue), TRUE);
  gtk_window_set_position(GTK_WINDOW(Dialogue),GTK_WIN_POS_CENTER);

  Label = gtk_label_new(_("Are you sure to delete \nthe selected atom? \n"));
  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type( GTK_FRAME(frame),GTK_SHADOW_ETCHED_OUT);

  gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
   gtk_box_pack_start( GTK_BOX(GTK_DIALOG(Dialogue)->vbox), frame,TRUE,TRUE,0);

  gtk_widget_show (frame);

  vboxframe = create_vbox(frame);

  gtk_box_pack_start(GTK_BOX(vboxframe), Label,TRUE,TRUE,0);

  gtk_widget_realize(Dialogue);

  Bouton = create_button(Dialogue,"No");
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Dialogue)->action_area), Bouton,TRUE,TRUE,0);
  g_signal_connect_swapped(G_OBJECT(Bouton), "clicked", (GCallback)gtk_widget_destroy, GTK_OBJECT(Dialogue));
  GTK_WIDGET_SET_FLAGS(Bouton, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(Bouton);

  Bouton = create_button(Dialogue,"Yes");
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Dialogue)->action_area), Bouton,TRUE,TRUE,0);
  g_signal_connect(G_OBJECT(Bouton), "clicked",(GCallback)DelAtomList, NULL);
  g_signal_connect_swapped(G_OBJECT(Bouton), "clicked",(GCallback)gtk_widget_destroy, GTK_OBJECT(Dialogue));
  GTK_WIDGET_SET_FLAGS(Bouton, GTK_CAN_DEFAULT);

  gtk_widget_show_all(Dialogue);
}
