name_table_get_name(Name_table *tbl, Module_table *m, symbol_kind kind, int entry)
{
    int m_entry = get_m_entry(tbl, m);

    switch (kind) {
    case KIND_VAR:
        return tbl->var_name[m_entry][entry];
    case KIND_ARRAY:
        return tbl->array_name[m_entry][entry];
    case KIND_SYNC:
        return tbl->sync_name[m_entry][entry];
    default:
        return NULL;
    }
}
