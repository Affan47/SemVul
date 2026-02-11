NextInterestingTime( void ) const
{

    REAL ret = LastTime();


    gDestination * run = currentDestination;
    while ( run )
    {
        REAL time = run->GetGameTime();
        if ( time > ret )
            ret = time;
        run = run->next;
    }

    return ret;
}
