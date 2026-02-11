show_edit_box(gint edit_type)
{
    const gchar *markup;
    HybridAccount *account;


    if (!(account = hybrid_blist_get_current_account())) {
        return;
    }

    hybrid_head->edit_account = account;
    hybrid_head->edit_state = edit_type;

    switch (edit_type) {
        case HYBRID_HEAD_EDIT_NAME:

            markup = _("<b>Please input the name:</b>");

            if (account->nickname) {
                gtk_entry_set_text(GTK_ENTRY(hybrid_head->edit_entry),
                        account->nickname);
            }

            break;
        case HYBRID_HEAD_EDIT_STATUS:

            markup = _("<b>Please input the status:</b>");

            if (account->status_text) {
                gtk_entry_set_text(GTK_ENTRY(hybrid_head->edit_entry),
                        account->status_text);
            }

            break;
        default:
            return;
    }


    gtk_label_set_markup(GTK_LABEL(hybrid_head->edit_label), markup);

    gtk_widget_hide(hybrid_head->eventbox);
    gtk_widget_show(hybrid_head->editbox);

    gtk_widget_grab_focus(hybrid_head->edit_entry);
}
