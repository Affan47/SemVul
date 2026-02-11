update_dialog_text (GsmInhibitDialog *dialog)
{
        const char *description_text;
        const char *header_text;
        GtkWidget  *widget;

        if (model_has_one_entry (GTK_TREE_MODEL (dialog->priv->list_store))) {
                g_debug ("Found one entry in model");
                header_text = _("A program is still running:");
                description_text = _("Waiting for the program to finish. Interrupting the program may cause you to lose work.");
        } else {
                g_debug ("Found multiple entries (or none) in model");
                header_text = _("Some programs are still running:");
                description_text = _("Waiting for programs to finish. Interrupting these programs may cause you to lose work.");
        }

        widget = GTK_WIDGET (gtk_builder_get_object (dialog->priv->xml,
                                                     "header-label"));
        if (widget != NULL) {
                char *markup;
                markup = g_strdup_printf ("<b>%s</b>", header_text);
                gtk_label_set_markup (GTK_LABEL (widget), markup);
                g_free (markup);
        }

        widget = GTK_WIDGET (gtk_builder_get_object (dialog->priv->xml,
                                                     "description-label"));
        if (widget != NULL) {
                gtk_label_set_text (GTK_LABEL (widget), description_text);
        }
}
