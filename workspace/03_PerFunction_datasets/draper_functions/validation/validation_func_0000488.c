name_update(GtkWidget *widget, deskno_priv *dc)
{
    char buffer [15];

    ENTER;
    dc->deskno = get_net_current_desktop();
    sprintf(buffer, "<b>%d</b>", dc->deskno + 1);
    gtk_label_set_markup(GTK_LABEL(dc->namew), buffer);
    RET(TRUE);
}
