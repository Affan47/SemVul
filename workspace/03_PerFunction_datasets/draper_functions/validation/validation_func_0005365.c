add_configuration_dialog(struct w *widgets)
{
    gchar *utf8=NULL;
    GtkTextBuffer *text_buffer;
    gchar *info;
    GtkWidget *add_conf_vbox, *add_conf_textview;

    widgets->add_configuration_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW (widgets->add_configuration_window), GTK_WIN_POS_CENTER);

    gtk_widget_set_size_request(widgets->add_configuration_window, 400, 100);


    info = g_strdup_printf(_("GBINDADMIN %s add a default configuration ?\n"), VERSION);
    utf8 = g_locale_to_utf8(info, strlen(info), NULL, NULL, NULL);
    gtk_window_set_title(GTK_WINDOW(widgets->add_configuration_window), utf8);
    g_free(info);

    add_conf_vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (widgets->add_configuration_window), add_conf_vbox);

    add_conf_textview = gtk_text_view_new();
    gtk_container_add (GTK_CONTAINER (add_conf_vbox), add_conf_textview);

    g_signal_connect(GTK_WINDOW(widgets->add_configuration_window), "delete_event",
		     G_CALLBACK(gtk_widget_destroy), NULL);

    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(add_conf_textview));
    info = g_strdup_printf(_("Could not find all neccesary files in BIND's chroot directory.\nShould the missing files and directories be added here ? :\n%s\n"), CHROOT_PATH_BUF);
    utf8 = g_locale_to_utf8(info, strlen(info), NULL, NULL, NULL);
    g_free(info);
    if( utf8!=NULL )
    {

        gtk_text_buffer_set_text(text_buffer, utf8, strlen(utf8));
        g_free(utf8);
    }

    GtkWidget *add_conf_hbuttonbox = gtk_hbutton_box_new();
    gtk_box_pack_start(GTK_BOX(add_conf_vbox), add_conf_hbuttonbox, FALSE, FALSE, 0);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(add_conf_hbuttonbox), GTK_BUTTONBOX_SPREAD);

    GtkWidget *yes_add_conf_button = gtk_button_new_from_stock(GTK_STOCK_YES);
    gtk_container_add(GTK_CONTAINER(add_conf_hbuttonbox), yes_add_conf_button);
    g_signal_connect_swapped(G_OBJECT(yes_add_conf_button), "clicked",
                             G_CALLBACK(add_configuration), widgets);

    GtkWidget *cancel_add_conf_button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    gtk_container_add(GTK_CONTAINER(add_conf_hbuttonbox), cancel_add_conf_button);
    g_signal_connect_swapped(G_OBJECT(cancel_add_conf_button), "clicked",
                             G_CALLBACK(add_configuration_canceled), widgets);

    gtk_widget_show(widgets->add_configuration_window);
    gtk_widget_show(add_conf_vbox);
    gtk_widget_show(add_conf_textview);
    gtk_widget_show(add_conf_hbuttonbox);
    gtk_widget_show(yes_add_conf_button);
    gtk_widget_show(cancel_add_conf_button);
}
