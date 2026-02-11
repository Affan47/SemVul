main ( int argc, const char **argv )
{
    int r = 1;
    if ( us_testutil_start ( 4096, 4096, argc, argv ) )
    {
#if US_ENABLE_LOGGING
        us_logger_printer_start ( us_testutil_printer_stdout, us_testutil_printer_stderr );
#endif
        us_log_set_level ( US_LOG_LEVEL_DEBUG );
        us_log_info ( "Hello world from %s compiled on %s", __FILE__, __DATE__ );
        if ( us_example_http_client ( argc, argv ) )
            r = 0;
        us_log_info ( "Finishing %s", argv[0] );
        us_logger_finish();
        us_testutil_finish();
    }
    return r;
}
