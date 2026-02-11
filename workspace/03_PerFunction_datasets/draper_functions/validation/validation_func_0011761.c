load_all_taxtables( GncSqlBackend* be )
{
    GncSqlStatement* stmt;
    GncSqlResult* result;

    g_return_if_fail( be != NULL );


    stmt = gnc_sql_create_select_statement( be, TT_TABLE_NAME );
    result = gnc_sql_execute_select_statement( be, stmt );
    gnc_sql_statement_dispose( stmt );
    if ( result != NULL )
    {
        GncSqlRow* row;
        GList* tt_needing_parents = NULL;

        row = gnc_sql_result_get_first_row( result );
        while ( row != NULL )
        {
            load_single_taxtable( be, row, &tt_needing_parents );
            row = gnc_sql_result_get_next_row( result );
        }
        gnc_sql_result_dispose( result );


        if ( tt_needing_parents != NULL )
        {
            gboolean progress_made = TRUE;
            GList* elem;

            while ( progress_made )
            {
                progress_made = FALSE;
                for ( elem = tt_needing_parents; elem != NULL; elem = g_list_next( elem ) )
                {
                    taxtable_parent_guid_struct* s = (taxtable_parent_guid_struct*)elem->data;
                    tt_set_parent( s->tt, &s->guid );
                    tt_needing_parents = g_list_delete_link( tt_needing_parents, elem );
                    progress_made = TRUE;
                }
            }
        }
    }
}
