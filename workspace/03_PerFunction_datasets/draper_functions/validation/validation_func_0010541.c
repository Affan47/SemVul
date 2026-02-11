gnc_reconcile_view_toggle_split (GNCReconcileView *view, Split *split)
{
    Split *current;

    g_return_if_fail (GNC_IS_RECONCILE_VIEW (view));
    g_return_if_fail (view->reconciled != NULL);

    current = g_hash_table_lookup (view->reconciled, split);

    if (current == NULL)
        g_hash_table_insert (view->reconciled, split, split);
    else
        g_hash_table_remove (view->reconciled, split);
}
