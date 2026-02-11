first_dtu_entry_table(Dtu_trans_group *trans)
{
    Dtu_entry_table *dpt;

    if (trans == NULL || trans->entry_head == NULL) {
        return NULL;
    }

    dpt = trans->entry_head;

    return dpt;
}
