Activate(REAL x, bool delayed )
{
    delayedValue_ = x;

    if ( !delayed || !Delayable() )
    {
        lastValue_ = x;
        return this->DoActivate( x );
    }

    return true;
}
