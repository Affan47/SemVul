create_orbit_selector   (GKeyFile *cfg, GtkBox *vbox)
{
    GtkWidget   *label;
    GtkWidget   *hbox;
    gint         onum;

    hbox = gtk_hbox_new (FALSE, 10);
    gtk_box_pack_start (vbox, hbox, FALSE, TRUE, 0);

    label = gtk_label_new (_("Display ground track for"));
    gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

    orbit = gtk_spin_button_new_with_range (1, 10, 1);
    gtk_spin_button_set_digits (GTK_SPIN_BUTTON (orbit), 0);
    gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (orbit), TRUE);

    if (cfg != NULL) {
        onum = mod_cfg_get_int (cfg,
                                MOD_CFG_MAP_SECTION,
                                MOD_CFG_MAP_TRACK_NUM,
                                SAT_CFG_INT_MAP_TRACK_NUM);
    }
    else {
        onum = sat_cfg_get_int (SAT_CFG_INT_MAP_TRACK_NUM);
    }
    gtk_spin_button_set_value (GTK_SPIN_BUTTON (orbit), onum);
    g_signal_connect (G_OBJECT (orbit), "value-changed",
                      G_CALLBACK (orbit_changed), NULL);

    gtk_box_pack_start (GTK_BOX (hbox), orbit, FALSE, FALSE, 0);

    label = gtk_label_new (_("orbit(s)"));
    gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

}
