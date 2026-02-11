find_by_account (gpointer find_data, gpointer user_data)
{
    Account *account = find_data;
    AccountWindow *aw = user_data;

    if (!aw)
        return FALSE;

    return guid_equal (&aw->account, xaccAccountGetGUID (account));
}
