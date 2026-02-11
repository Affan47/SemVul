create_character_set_sensitive(int sensitive)
{
    int i;

    gtk_widget_set_sensitive(button_cc_done, sensitive);
    gtk_widget_set_sensitive(button_choose_starting_map, sensitive);
    gtk_widget_set_sensitive(entry_new_character_name, sensitive);
    gtk_widget_set_sensitive(combobox_rs, sensitive);
    gtk_widget_set_sensitive(combobox_cs, sensitive);


    for (i=0; i<NUM_NEW_CHAR_STATS; i++)
        gtk_widget_set_sensitive(spinbutton_cc[i], sensitive);


    if (starting_map_number)
        gtk_widget_show(button_choose_starting_map);
    else
        gtk_widget_hide(button_choose_starting_map);
}
