gnc_ofx_kvp_get_assoc_account(const Account* investment_account)
{
    kvp_frame * acc_frame;
    kvp_value * kvp_val;
    Account *result = NULL;

    g_assert(investment_account);

    acc_frame = xaccAccountGetSlots(investment_account);
    kvp_val = kvp_frame_get_slot(acc_frame, KEY_ASSOC_INCOME_ACCOUNT);
    if (kvp_val != NULL)
    {
        result = xaccAccountLookup(kvp_value_get_guid(kvp_val),
                                   gnc_account_get_book(investment_account));
    }
    return result;
}
