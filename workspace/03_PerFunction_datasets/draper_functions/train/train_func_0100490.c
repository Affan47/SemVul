gsb_data_currency_link_init_variables ( void )
{
    if ( currency_link_list )
    {
        GSList* tmp_list = currency_link_list;
        while ( tmp_list )
        {
	    struct_currency_link *currency_link;
	    currency_link = tmp_list -> data;
	    tmp_list = tmp_list -> next;
            _g_data_currency_link_free ( currency_link );
        }
	g_slist_free ( currency_link_list );
    }
    currency_link_list = NULL;
    currency_link_buffer = NULL;
    return FALSE;
}
