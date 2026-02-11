test_book_use_trading_accounts( Fixture *fixture, gconstpointer pData )
{
    const char *slot_path;


    slot_path = (const char *) g_strconcat( KVP_OPTION_PATH, "/", OPTION_SECTION_ACCOUNTS, "/", OPTION_NAME_TRADING_ACCOUNTS, NULL );
    g_assert( slot_path != NULL );

    g_test_message( "Testing when no trading accounts are used" );
    g_assert( qof_book_use_trading_accounts( fixture-> book ) == FALSE );

    g_test_message( "Testing with incorrect slot path and correct value - t" );
    qof_book_set_string_option( fixture->book, OPTION_NAME_TRADING_ACCOUNTS, "t" );
    g_assert( qof_book_use_trading_accounts( fixture-> book ) == FALSE );

    g_test_message( "Testing with existing trading accounts set to true - t" );
    qof_book_set_string_option( fixture->book, slot_path, "t" );
    g_assert( qof_book_use_trading_accounts( fixture-> book ) == TRUE );

    g_test_message( "Testing with existing trading accounts and incorrect value - tt" );
    qof_book_set_string_option( fixture->book, slot_path, "tt" );
    g_assert( qof_book_use_trading_accounts( fixture-> book ) == FALSE );

}
