account_restore_fail_handler(gpointer data_for_children,
                             GSList* data_from_children,
                             GSList* sibling_data,
                             gpointer parent_data,
                             gpointer global_data,
                             gpointer *result,
                             const gchar *tag)
{
    Account *acc = (Account *) * result;
    if (acc)
    {
        xaccAccountBeginEdit (acc);
        xaccAccountDestroy(acc);
    }
}
