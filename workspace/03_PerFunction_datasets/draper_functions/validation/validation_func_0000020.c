classement_sliste_transactions_par_date ( gpointer transaction_pointer_1,
                        gpointer transaction_pointer_2 )
{
    const GDate *date;
    gint transaction_number_1;
    gint transaction_number_2;

    transaction_number_1 = gsb_data_transaction_get_transaction_number (
                        transaction_pointer_1 );
    transaction_number_2 = gsb_data_transaction_get_transaction_number (
                        transaction_pointer_2 );
    date = gsb_data_transaction_get_date (transaction_number_1);
    if ( date )
        return ( g_date_compare ( date,
                        gsb_data_transaction_get_date (transaction_number_2) ));
    else
        return -1;
}
