x_window_create_drawing(GtkWidget *drawbox, GSCHEM_TOPLEVEL *w_current)
{

  w_current->drawing_area = gtk_drawing_area_new ();


  gtk_drawing_area_size (GTK_DRAWING_AREA (w_current->drawing_area),
                         w_current->win_width,
                         w_current->win_height);

  gtk_box_pack_start (GTK_BOX (drawbox), w_current->drawing_area,
                      TRUE, TRUE, 0);
  GTK_WIDGET_SET_FLAGS (w_current->drawing_area, GTK_CAN_FOCUS );
  gtk_widget_grab_focus (w_current->drawing_area);
  gtk_widget_show (w_current->drawing_area);

}
