gsb_data_partial_balance_get_current_amount ( gint partial_balance_number )
{
    struct_partial_balance *partial_balance;
    gsb_real solde = null_real;
    gchar **tab;
    gint i;

    partial_balance = gsb_data_partial_balance_get_structure ( partial_balance_number );

    if ( !partial_balance )
        return null_real;

    if ( partial_balance -> liste_cptes == NULL ||
     strlen ( partial_balance -> liste_cptes ) == 0 )
        return null_real;

    tab = g_strsplit ( partial_balance -> liste_cptes, ";", 0 );
    for ( i = 0; tab[i]; i++ )
    {
        gsb_real tmp_real;
        gint account_nb;
        gint account_currency;
        gint link_number;

        account_nb = utils_str_atoi ( tab[i] );
        account_currency = gsb_data_account_get_currency ( account_nb );
        tmp_real = gsb_data_account_get_current_balance ( account_nb );

        if ( tmp_real.mantissa != 0 && partial_balance -> currency != account_currency )
        {
            if ( ( link_number = gsb_data_currency_link_search ( account_currency,
                        partial_balance -> currency ) ) )
            {
                if ( gsb_data_currency_link_get_first_currency (
                        link_number) == account_currency )
                    tmp_real = gsb_real_mul ( tmp_real,
                                gsb_data_currency_link_get_change_rate ( link_number ) );
                else
                    tmp_real = gsb_real_div ( tmp_real,
                                gsb_data_currency_link_get_change_rate ( link_number ) );
            }
        }
        solde = gsb_real_add ( solde, tmp_real );
    }

    return solde;
}
