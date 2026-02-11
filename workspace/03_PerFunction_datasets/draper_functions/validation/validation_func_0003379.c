gnc_ui_new_accounts_from_name_with_defaults (const char *name,
        GList *valid_types,
        const gnc_commodity * default_commodity,
        Account * parent)
{
    QofBook *book;
    AccountWindow *aw;
    Account *base_account = NULL;
    Account *created_account = NULL;
    gchar ** subaccount_names;
    gint response;
    gboolean done = FALSE;

    ENTER("name %s, valid %p, commodity %p, account %p",
          name, valid_types, default_commodity, parent);
    book = gnc_get_current_book();
    if (!name || *name == '\0')
    {
        subaccount_names = NULL;
        base_account = NULL;
    }
    else
        subaccount_names = gnc_split_account_name (book, name, &base_account);

    if (parent != NULL)
    {
        base_account = parent;
    }
    aw = gnc_ui_new_account_window_internal (book, base_account, subaccount_names,
            valid_types, default_commodity,
            TRUE);

    while (!done)
    {
        response = gtk_dialog_run (GTK_DIALOG(aw->dialog));


        gnc_account_window_response_cb (GTK_DIALOG(aw->dialog), response, (gpointer)aw);

        switch (response)
        {
        case GTK_RESPONSE_OK:
            created_account = aw->created_account;
            done = (created_account != NULL);
            break;

        case GTK_RESPONSE_HELP:
            done = FALSE;
            break;

        default:
            done = TRUE;
            break;
        }
    }

    close_handler(aw);
    LEAVE("created %s (%p)", xaccAccountGetName(created_account), created_account);
    return created_account;
}
