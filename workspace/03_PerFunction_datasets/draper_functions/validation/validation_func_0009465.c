xaccAccountDeleteOldData (Account *account)
{
    if (!account) return;
    xaccAccountBeginEdit (account);

    kvp_frame_set_slot_nc (account->inst.kvp_data, "old-currency", NULL);
    kvp_frame_set_slot_nc (account->inst.kvp_data, "old-security", NULL);
    kvp_frame_set_slot_nc (account->inst.kvp_data, "old-currency-scu", NULL);
    kvp_frame_set_slot_nc (account->inst.kvp_data, "old-security-scu", NULL);
    qof_instance_set_dirty (QOF_INSTANCE (account));
    xaccAccountCommitEdit (account);
}
