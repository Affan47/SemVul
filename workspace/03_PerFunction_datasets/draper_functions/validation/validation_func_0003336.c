load_lot_guid( const GncSqlBackend* be, GncSqlRow* row,
                QofSetterFunc setter, gpointer pObject,
               const GncSqlColumnTableEntry* table_row )
{
    const GValue* val;
    GncGUID guid;
    GNCLot* lot;

    g_return_if_fail( be != NULL );
    g_return_if_fail( row != NULL );
    g_return_if_fail( pObject != NULL );
    g_return_if_fail( table_row != NULL );

    val = gnc_sql_row_get_value_at_col_name( row, table_row->col_name );
    if ( val != NULL && G_VALUE_HOLDS_STRING( val ) && g_value_get_string( val ) != NULL )
    {
        (void)string_to_guid( g_value_get_string( val ), &guid );
        lot = gnc_lot_lookup( &guid, be->book );
        if ( lot != NULL )
        {
            if ( table_row->gobj_param_name != NULL )
            {
                g_object_set( pObject, table_row->gobj_param_name, lot, NULL );
            }
            else
            {
                g_return_if_fail( setter != NULL );
                (*setter)( pObject, (const gpointer)lot );
            }
        }
        else
        {
            PWARN( "Lot ref '%s' not found", g_value_get_string( val ) );
        }
    }
}
