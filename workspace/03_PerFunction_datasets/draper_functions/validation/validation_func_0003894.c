mousePressed( bool pressed )
{
    DEBUG_BLOCK

    if( pressed && data( 0 ) != QVariant() )
    {
        debug() << data( 0 ).toString();
        emit appletChosen( data( 0 ).toString() );
    }
}
