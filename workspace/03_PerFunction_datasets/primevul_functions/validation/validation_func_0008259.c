sync_is_active(Slapi_Entry *e, Slapi_PBlock *pb)
{
    if (pb == NULL) {

        return (0);
    } else {

        return (sync_is_active_scope(slapi_entry_get_sdn_const(e), pb));
    }
}
