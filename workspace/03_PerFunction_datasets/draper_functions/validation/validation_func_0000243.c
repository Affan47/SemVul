gsb_csv_export_account ( const gchar *filename, gint account_number )
{
    FILE *csv_file;
    GSList *pTransactionList;
    GSList *tmp_list;

    csv_file = gsb_csv_export_open_file ( filename );

    if ( !csv_file )
        return FALSE;

    if ( g_csv_with_title_line )
        gsb_csv_export_title_line ( csv_file, TRUE );


    if ( csv_field_tiers )
        g_free ( csv_field_tiers );

    csv_field_tiers = g_strconcat (_("Initial balance") , " [",
                        gsb_data_account_get_name ( account_number ),
                        "]", NULL );


    current_balance = gsb_data_account_get_init_balance ( account_number, -1);

    tmp_list = gsb_data_archive_store_get_archives_list ( );
    while ( tmp_list )
    {
        gint archive_store_number;

        archive_store_number = gsb_data_archive_store_get_number ( tmp_list -> data );

        if ( gsb_data_archive_store_get_account_number ( archive_store_number ) == account_number )
            current_balance = gsb_real_add ( current_balance,
                                gsb_data_archive_store_get_balance ( archive_store_number ) );

        tmp_list = tmp_list -> next;
    }


    CSV_CLEAR_FIELD ( csv_field_solde );
    csv_field_solde = gsb_real_get_string ( current_balance );
    if ( current_balance.mantissa >= 0 )
    {
        CSV_CLEAR_FIELD ( csv_field_credit );
        csv_field_credit = gsb_real_get_string ( current_balance );
    }
    else
    {
        CSV_CLEAR_FIELD ( csv_field_debit );
        csv_field_debit = gsb_real_get_string ( gsb_real_abs ( current_balance ) );
    }

    csv_add_record ( csv_file, TRUE, TRUE );


    pTransactionList = gsb_data_transaction_get_transactions_list ( );
    tmp_list = g_slist_sort ( g_slist_copy ( pTransactionList ),
                        (GCompareFunc) gsb_csv_export_sort_by_value_date_or_date );

    while ( tmp_list )
    {
        gint pTransaction;

        pTransaction = gsb_data_transaction_get_transaction_number ( tmp_list -> data );

        if ( gsb_data_transaction_get_account_number ( pTransaction ) == account_number )
        {


            gsb_csv_export_transaction ( pTransaction, csv_file, TRUE);
        }

        tmp_list = tmp_list -> next;
    }

    fclose ( csv_file );
    g_slist_free ( tmp_list );


    return TRUE;
}
