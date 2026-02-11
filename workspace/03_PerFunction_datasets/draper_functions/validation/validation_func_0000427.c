ibus_lookup_table_clear (IBusLookupTable *table)
{
    g_assert (IBUS_IS_LOOKUP_TABLE (table));

    gint index;

    for (index = 0; index < table->candidates->len; index ++) {
        g_object_unref (g_array_index (table->candidates, IBusText *, index));
    }

    g_array_set_size (table->candidates, 0);

    table->cursor_pos = 0;
}
