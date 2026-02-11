gnc_payment_dialog_owner_changed (PaymentWindow *pw)
{
    Account *last_acct = NULL;
    GncGUID *guid = NULL;
    KvpValue* value;
    KvpFrame* slots;
    GncOwner *owner = &pw->owner;


    pw->invoice = NULL;


    slots = gncOwnerGetSlots(owner);
    if (slots)
    {
        value = kvp_frame_get_slot_path(slots, "payment", "last_acct", NULL);
        if (value)
        {
            guid = kvp_value_get_guid(value);
        }
    }


    if (pw->acct_types)
    {
        g_list_free(pw->acct_types);
        pw->acct_types = NULL;
    }

    if (pw->acct_commodities)
    {
        g_list_free(pw->acct_commodities);
        pw->acct_commodities = NULL;
    }

    pw->acct_types = gncOwnerGetAccountTypesList(owner);
    if (gncOwnerIsValid(owner))
        pw->acct_commodities = gncOwnerGetCommoditiesList (owner);
    pw->post_acct = gnc_account_select_combo_fill (pw->post_combo, pw->book, pw->acct_types, pw->acct_commodities);


    gnc_payment_window_fill_docs_list (pw);

    if (guid)
    {
        last_acct = xaccAccountLookup(guid, pw->book);
    }


    if (last_acct && !gnc_payment_dialog_has_pre_existing_txn(pw))
    {
        gnc_tree_view_account_set_selected_account(GNC_TREE_VIEW_ACCOUNT(pw->acct_tree),
                last_acct);
    }
}
