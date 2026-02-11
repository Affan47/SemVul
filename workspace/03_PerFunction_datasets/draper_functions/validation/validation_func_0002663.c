fx_remove(HybridAccount *account, HybridBuddy *buddy)
{
    fetion_account *ac;

    ac = hybrid_account_get_protocol_data(account);

    if (fetion_buddy_remove(ac, buddy->id) != HYBRID_OK) {
        return FALSE;
    }

    return TRUE;
}
