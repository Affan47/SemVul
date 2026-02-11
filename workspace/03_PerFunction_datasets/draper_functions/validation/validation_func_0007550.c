gnc_sql_save_schedxaction( GncSqlBackend* be, QofInstance* inst )
{
    SchedXaction* pSx;
    const GncGUID* guid;
    gint op;
    gboolean is_infant;
    gboolean is_ok;

    g_return_val_if_fail( be != NULL, FALSE );
    g_return_val_if_fail( inst != NULL, FALSE );
    g_return_val_if_fail( GNC_IS_SX(inst), FALSE );

    pSx = GNC_SX(inst);

    is_infant = qof_instance_get_infant( inst );
    if ( qof_instance_get_destroying( inst ) )
    {
        op = OP_DB_DELETE;
    }
    else if ( be->is_pristine_db || is_infant )
    {
        op = OP_DB_INSERT;
    }
    else
    {
        op = OP_DB_UPDATE;
    }
    is_ok = gnc_sql_do_db_operation( be, op, SCHEDXACTION_TABLE, GNC_SX_ID, pSx, col_table );
    guid = qof_instance_get_guid( inst );
    if ( op == OP_DB_INSERT || op == OP_DB_UPDATE )
    {
        gnc_sql_recurrence_save_list( be, guid, gnc_sx_get_schedule( pSx ) );
    }
    else
    {
        gnc_sql_recurrence_delete( be, guid );
    }

    if ( is_ok )
    {

        if ( op == OP_DB_INSERT || op == OP_DB_UPDATE )
        {
            is_ok = gnc_sql_slots_save( be, guid, is_infant, qof_instance_get_slots( inst ) );
        }
        else
        {
            is_ok = gnc_sql_slots_delete( be, guid );
        }
    }

    return is_ok;
}
