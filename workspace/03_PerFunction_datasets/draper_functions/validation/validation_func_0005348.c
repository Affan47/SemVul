wait_for_release( XKeyEvent * ev )
{
    KeySym ksm;

    if ( ( ksm = XLookupKeysym( ev, 0 ) ) == NoSymbol )
        return;

    while ( fl_keysym_pressed( ksm ) )
    {
        XSync( flx->display, 0 );
        fl_msleep( 15 );
    }
}
