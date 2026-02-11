create_window_listing (void)
{
  GtkWidget *window_listing;
  GdkPixbuf *window_listing_icon_pixbuf;
  GtkWidget *listing_vbox;
  GtkWidget *hbuttonbox1;
  GtkWidget *listing_save;
  GtkWidget *listing_print;

  window_listing = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window_listing), _("Assembler Listing"));
  gtk_window_set_position (GTK_WINDOW (window_listing), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window_listing), 500, 400);
  window_listing_icon_pixbuf = create_pixbuf ("gnusim8085.svg");
  if (!window_listing_icon_pixbuf)
    window_listing_icon_pixbuf = create_pixbuf ("gnusim8085.ico");

  if (window_listing_icon_pixbuf)
    {
      gtk_window_set_icon (GTK_WINDOW (window_listing), window_listing_icon_pixbuf);
      gdk_pixbuf_unref (window_listing_icon_pixbuf);
    }

  listing_vbox = gtk_vbox_new (FALSE, 2);
  gtk_widget_show (listing_vbox);
  gtk_container_add (GTK_CONTAINER (window_listing), listing_vbox);
  gtk_container_set_border_width (GTK_CONTAINER (listing_vbox), 5);

  hbuttonbox1 = gtk_hbutton_box_new ();
  gtk_widget_show (hbuttonbox1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox1), GTK_BUTTONBOX_CENTER);
  gtk_box_pack_start (GTK_BOX (listing_vbox), hbuttonbox1, FALSE, FALSE, 0);

  listing_save = gtk_button_new ();
  gtk_button_set_label (GTK_BUTTON(listing_save), _("Save to file"));
  gtk_button_set_image (GTK_BUTTON(listing_save), gtk_image_new_from_stock (GTK_STOCK_SAVE_AS, GTK_ICON_SIZE_BUTTON));
  gtk_widget_show (listing_save);
  gtk_box_pack_start (GTK_BOX (hbuttonbox1), listing_save, FALSE, FALSE, 0);
  GTK_WIDGET_SET_FLAGS (listing_save, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) listing_save, "clicked",
                    G_CALLBACK (on_listing_save_clicked),
                    NULL);

  listing_print = gtk_button_new_from_stock (GTK_STOCK_PRINT);
  gtk_widget_show (listing_print);
  gtk_box_pack_start (GTK_BOX (hbuttonbox1), listing_print, FALSE, FALSE, 0);
  GTK_WIDGET_SET_FLAGS (listing_print, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) listing_print, "clicked",
                    G_CALLBACK (on_listing_print_clicked),
                    NULL);


  GLADE_HOOKUP_OBJECT_NO_REF (window_listing, window_listing, "window_listing");
  GLADE_HOOKUP_OBJECT (window_listing, listing_vbox, "listing_vbox");
  GLADE_HOOKUP_OBJECT (window_listing, hbuttonbox1, "hbuttonbox1");
  GLADE_HOOKUP_OBJECT (window_listing, listing_save, "listing_save");
  GLADE_HOOKUP_OBJECT (window_listing, listing_save, "listing_print");

  return window_listing;
}
