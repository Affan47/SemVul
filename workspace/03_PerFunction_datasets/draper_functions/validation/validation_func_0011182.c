add_account_local(GncExampleAccount *gea, Account *act)
{
    gnc_commodity_table *table;

    table = gnc_commodity_table_get_table (gea->book);

    clear_up_account_commodity(table, act,
                               xaccAccountGetCommodity,
                               xaccAccountSetCommodity);

    xaccAccountScrubCommodity (act);

    if (xaccAccountGetType(act) == ACCT_TYPE_ROOT)
    {
        gea->root = act;
    }
    else if (!gnc_account_get_parent(act))
    {
        if (!gea->root)
        {
            g_warning("The example account file should declared a ROOT "
                      "account before declaring any other accounts.");
            gea->root = gnc_book_get_root_account(gea->book);
        }
        gnc_account_append_child(gea->root, act);
    }
}
