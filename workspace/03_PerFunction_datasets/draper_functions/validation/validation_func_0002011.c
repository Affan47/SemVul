get_payment_entry (VirtualLocation virt_loc,
                                       gboolean translate,
                                       gboolean *conditionally_changed,
                                       gpointer user_data)
{
    GncEntryLedger *ledger = user_data;
    GncEntry *entry;
    GncEntryPaymentType type;

    entry = gnc_entry_ledger_get_entry (ledger, virt_loc.vcell_loc);

    if (!entry)
        return "";

    type = gncEntryGetBillPayment (entry);

    switch (type)
    {
    case GNC_PAYMENT_CASH:
        return _("Cash");
    case GNC_PAYMENT_CARD:
        return _("Charge");
    default:
        g_warning ("Invalid payment type: %d", type);
        return "";
    }
}
