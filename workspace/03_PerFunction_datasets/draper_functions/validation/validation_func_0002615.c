init_web_browser(GtkWidget *parent) {
    browser = g_new0(WebBrowser, 1);

    create_menubar();
    create_toolbar();
    create_browser();
    create_statusbar();

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX (vbox), browser->menubar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX (vbox), browser->toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX (vbox), browser->browser_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX (vbox), GTK_WIDGET(browser->statusbar), FALSE, FALSE, 0);

    if (GTK_IS_SCROLLED_WINDOW(parent))
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(parent), vbox);
    else
        gtk_container_add(GTK_CONTAINER (parent), vbox);

    return browser;
}
